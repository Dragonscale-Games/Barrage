/* ======================================================================== */
/*!
 * \file            HierarchyWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Displays all pools in current game scene.
 */
 /* ======================================================================== */

#include "HierarchyWidget.hpp"
#include "Editor.hpp"

#include "Widgets/Popups/Object/ObjectPopupWidget.hpp"
#include "Widgets/Popups/Pool/PoolPopupWidget.hpp"
#include "Widgets/Popups/Scene/ScenePopupWidget.hpp"

namespace Barrage
{
  void HierarchyWidget::Use()
  {
    ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_NoMove);

    if (!Editor::Get().Data().selectedScene_.empty())
    {
      SceneGUI();
    }

    ImGui::End();
  }

  void HierarchyWidget::SceneGUI()
  {
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Text(Editor::Get().Data().selectedScene_.c_str());
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    bool itemClicked = false;

    PoolArchetypeMap& poolArchetypes = Engine::Get().Scenes().GetScene(Editor::Get().Data().selectedScene_)->GetPoolArchetypes();

    for (auto it = poolArchetypes.begin(); it != poolArchetypes.end(); ++it)
    {
      itemClicked |= PoolGUI(it->second);
    }

    if (!itemClicked && ImGui::IsWindowHovered())
    {
      if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) || ImGui::IsMouseClicked(ImGuiMouseButton_Right))
      {
        DeselectAll();

        if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
        {
          ImGui::OpenPopup("Scene Popup");
        }
      }
    }

    ScenePopupWidget::Use("Scene Popup");
  }

  bool HierarchyWidget::PoolGUI(PoolArchetype& poolArchetype)
  {
    bool itemClicked = false;
    const std::string& poolName = poolArchetype.GetName();
    std::string poolLabel = poolName;

    ImGui::PushID(poolName.c_str());

    ImGuiTreeNodeFlags pool_tree_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

    if (poolName == Editor::Get().Data().selectedPool_)
    {
      pool_tree_flags |= ImGuiTreeNodeFlags_Selected;
    }

    std::string poolCapacityLabel;

    if (Editor::Get().Data().gamePlaying_)
    {
      Space* space = Engine::Get().Spaces().GetSpace(Editor::Get().Data().editorSpace_);

      if (space)
      {
        Pool& pool = space->GetObjectManager().pools_.at(poolName);

        poolCapacityLabel = "(" + std::to_string(pool.ActiveObjectCount()) + "/" + std::to_string(poolArchetype.capacity_) + ")";
      }
    }
    else
    {
      poolCapacityLabel = "(" + std::to_string(poolArchetype.startingObjects_.size()) + "/" + std::to_string(poolArchetype.capacity_) + ")";
    }

    float freeSpace = ImGui::GetWindowWidth() - ImGui::CalcTextSize(poolLabel.c_str()).x - ImGui::CalcTextSize(poolCapacityLabel.c_str()).x;

    int numSpaces = static_cast<int>(freeSpace / ImGui::CalcTextSize(" ").x);
    numSpaces -= 5;
    if (numSpaces < 1)
    {
      numSpaces = 1;
    }

    for (int i = 0; i < numSpaces; ++i)
    {
      poolLabel += " ";
    }

    poolLabel += poolCapacityLabel;

    bool node_open = ImGui::TreeNodeEx(poolLabel.c_str(), pool_tree_flags);

    if (ImGui::IsItemClicked(ImGuiMouseButton_Left) || ImGui::IsItemClicked(ImGuiMouseButton_Right))
    {
      itemClicked = true;
      DeselectAll();
      Editor::Get().Data().selectedPool_ = poolName;

      if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
      {
        ImGui::OpenPopup("Pool Popup");
      }
    }

    PoolPopupWidget::Use("Pool Popup");

    if (node_open)
    {
      ObjectArchetypeMap& startingObjects = poolArchetype.startingObjects_;
      for (auto it = startingObjects.begin(); it != startingObjects.end(); ++it)
      {
        itemClicked |= ObjectGUI(poolName, it->second, false);
      }

      ObjectArchetypeMap& spawnArchetypes = poolArchetype.spawnArchetypes_;
      for (auto it = spawnArchetypes.begin(); it != spawnArchetypes.end(); ++it)
      {
        itemClicked |= ObjectGUI(poolName, it->second, true);
      }

      ObjectPopupWidget::Use("Object Popup");

      ImGui::TreePop();
    }

    ImGui::Spacing();
    ImGui::PopID();

    return itemClicked;
  }

  bool HierarchyWidget::ObjectGUI(const std::string poolName, ObjectArchetype& objectArchetype, bool isSpawnArchetype = false)
  {
    bool itemClicked = false;

    const std::string& objectName = objectArchetype.name_;

    ImGuiTreeNodeFlags object_tree_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

    if (poolName == Editor::Get().Data().selectedPool_)
    {
      if (isSpawnArchetype && objectName == Editor::Get().Data().selectedSpawnArchetype_)
      {
        object_tree_flags |= ImGuiTreeNodeFlags_Selected;
      }
      else if (!isSpawnArchetype && objectName == Editor::Get().Data().selectedStartingObject_)
      {
        object_tree_flags |= ImGuiTreeNodeFlags_Selected;
      }
    }

    std::string label;

    if (isSpawnArchetype)
    {
      label += "[S] ";
    }

    label += objectName;

    ImGui::TreeNodeEx(label.c_str(), object_tree_flags);

    if (ImGui::IsItemClicked(ImGuiMouseButton_Left) || ImGui::IsItemClicked(ImGuiMouseButton_Right))
    {
      itemClicked = true;
      Editor::Get().Data().selectedPool_ = poolName;

      if (isSpawnArchetype)
      {
        SelectSpawnArchetype(objectName);
      }
      else
      {
        SelectStartingObject(objectName);
      }
      
      if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
      {
        ImGui::OpenPopup("Object Popup");
      }
    }

    return itemClicked;
  }

  void HierarchyWidget::SelectStartingObject(const std::string name)
  {
    Editor::Get().Data().selectedStartingObject_ = name;
    Editor::Get().Data().selectedSpawnArchetype_ = std::string();
  }

  void HierarchyWidget::SelectSpawnArchetype(const std::string name)
  {
    Editor::Get().Data().selectedStartingObject_ = std::string();
    Editor::Get().Data().selectedSpawnArchetype_ = name;
  }

  void HierarchyWidget::DeselectAll()
  {
    Editor::Get().Data().selectedPool_ = std::string();
    Editor::Get().Data().selectedStartingObject_ = std::string();
    Editor::Get().Data().selectedSpawnArchetype_ = std::string();
  }
}