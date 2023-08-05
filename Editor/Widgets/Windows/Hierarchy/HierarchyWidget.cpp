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
  ImVec2 HierarchyWidget::size_ = ImVec2(0.0f, 0.0f);
  
  void HierarchyWidget::Use()
  {
    ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_NoMove);

    size_ = ImGui::GetWindowSize();

    if (!Editor::Instance->Data().selectedScene_.empty())
    {
      SceneGUI();
    }

    ImGui::End();
  }

  ImVec2 HierarchyWidget::GetSize()
  {
    return size_;
  }

  void HierarchyWidget::SceneGUI()
  {
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Text(Editor::Instance->Data().selectedScene_.c_str());
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    bool itemClicked = false;

    const std::vector<PoolArchetype*>& poolArchetypes = Engine::Instance->Scenes().GetScene(Editor::Instance->Data().selectedScene_)->GetPoolArchetypes();

    for (auto it = poolArchetypes.begin(); it != poolArchetypes.end(); ++it)
    {
      itemClicked |= PoolGUI(*it);
    }

    if (!itemClicked && ImGui::IsWindowHovered())
    {
      if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
      {
        DeselectAll();

        ImGui::OpenPopup("Scene Popup");
      }
      else if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
      {
        DeselectAll();
      }
    }

    ScenePopupWidget::Use("Scene Popup");
  }

  bool HierarchyWidget::PoolGUI(PoolArchetype* poolArchetype)
  {
    if (poolArchetype == nullptr)
    {
      return false;
    }
    
    bool itemClicked = false;
    const std::string& poolName = poolArchetype->GetName();
    std::string poolLabel = poolName;

    ImGui::PushID(poolName.c_str());

    ImGuiTreeNodeFlags pool_tree_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

    if (poolName == Editor::Instance->Data().selectedPool_)
    {
      pool_tree_flags |= ImGuiTreeNodeFlags_Selected;
    }

    std::string poolCapacityLabel;
    
    if (Editor::Instance->Data().gamePlaying_)
    {
      Space* space = Engine::Instance->Spaces().GetSpace(Editor::Instance->Data().selectedSpace_);

      if (space)
      {
        Pool* pool = space->GetObjectManager().GetPool(poolName);

        if (pool)
        {
          poolCapacityLabel = "(" + std::to_string(pool->GetActiveObjectCount()) + "/" + std::to_string(poolArchetype->GetCapacity()) + ")";
        }
      }
    }
    else
    {
      poolCapacityLabel = "(" + std::to_string(poolArchetype->GetStartingObjects().size()) + "/" + std::to_string(poolArchetype->GetCapacity()) + ")";
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

    if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
    {
      itemClicked = true;
      Editor::Instance->Data().selectedPool_ = poolName;
      Editor::Instance->Data().selectedObject_ = std::string();

      ImGui::OpenPopup("Pool Popup");
    }
    else if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
    {
      itemClicked = true;
      Editor::Instance->Data().selectedPool_ = poolName;
      Editor::Instance->Data().selectedObject_ = std::string();
    }

    PoolPopupWidget::Use("Pool Popup");

    if (node_open)
    {
      const std::vector<ObjectArchetype*> startingObjects = poolArchetype->GetStartingObjects();
      for (auto it = startingObjects.begin(); it != startingObjects.end(); ++it)
      {
        itemClicked |= ObjectGUI(poolName, *it);
      }

      const std::vector<ObjectArchetype*> spawnArchetypes = poolArchetype->GetSpawnArchetypes();
      for (auto it = spawnArchetypes.begin(); it != spawnArchetypes.end(); ++it)
      {
        itemClicked |= ObjectGUI(poolName, *it, true);
      }

      ObjectPopupWidget::Use("Object Popup");

      ImGui::TreePop();
    }

    ImGui::Spacing();
    ImGui::PopID();

    return itemClicked;
  }

  bool HierarchyWidget::ObjectGUI(const std::string poolName, ObjectArchetype* objectArchetype, bool isSpawnArchetype)
  {
    bool itemClicked = false;

    const std::string& objectName = objectArchetype->GetName();;

    ImGuiTreeNodeFlags object_tree_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

    if (poolName == Editor::Instance->Data().selectedPool_ && objectName == Editor::Instance->Data().selectedObject_)
    {
      object_tree_flags |= ImGuiTreeNodeFlags_Selected;
    }

    std::string label;

    if (isSpawnArchetype)
    {
      label += "[S] ";
    }

    label += objectName;

    ImGui::TreeNodeEx(label.c_str(), object_tree_flags);

    if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
    {
      itemClicked = true;
      Editor::Instance->Data().selectedPool_ = poolName;
      Editor::Instance->Data().selectedObject_ = objectName;

      ImGui::OpenPopup("Object Popup");
    }
    else if (ImGui::IsItemClicked())
    {
      itemClicked = true;
      Editor::Instance->Data().selectedPool_ = poolName;
      Editor::Instance->Data().selectedObject_ = objectName;
    }

    return itemClicked;
  }

  void HierarchyWidget::DeselectAll()
  {
    Editor::Instance->Data().selectedPool_ = std::string();
    Editor::Instance->Data().selectedObject_ = std::string();
  }
}