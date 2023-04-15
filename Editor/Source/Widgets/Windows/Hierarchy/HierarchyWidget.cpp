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
#include "Editor/Editor.hpp"

#include "Widgets/Popups/Object/ObjectPopupWidget.hpp"
#include "Widgets/Popups/Pool/PoolPopupWidget.hpp"
#include "Widgets/Popups/Scene/ScenePopupWidget.hpp"

namespace Barrage
{
  void HierarchyWidget::Use()
  {
    ImGui::Begin("Hierarchy");

    /*if (!Editor::Instance->Data().selectedScene_.empty())
    {
      ImGui::Separator();
      ImGui::Spacing();
      ImGui::Text(Editor::Instance->Data().selectedScene_.c_str());
      ImGui::Spacing();
      ImGui::Separator();
      ImGui::Spacing();

      bool itemClicked = false;

      const std::vector<PoolInfo>& pools = Engine::Instance->Scenes().GetScene(Editor::Instance->Data().selectedScene_)->startingPools_;

      for (auto it = pools.begin(); it != pools.end(); ++it)
      {
        ImGui::PushID(it->poolName_.c_str());
        
        const PoolInfo& pool = *it;
        
        ImGuiTreeNodeFlags pool_tree_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

        if (pool.poolName_ == Editor::Instance->Data().selectedPool_)
        {
          pool_tree_flags |= ImGuiTreeNodeFlags_Selected;
        }

        std::string poolLabel = pool.poolName_.data();

        PoolArchetype* poolArchetype = Engine::Instance->Spaces().GetSpace(Editor::Instance->Data().selectedSpace_.data())->GetObjectManager().GetPoolArchetype(pool.poolName_);

        if (poolArchetype)
        {
          std::string poolCapacityLabel = "(" + std::to_string(pool.objects_.size()) + "/" + std::to_string(poolArchetype->capacity_) + ")";

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
        }
        
        bool node_open = ImGui::TreeNodeEx(poolLabel.c_str(), pool_tree_flags);
        
        if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
        {
          itemClicked = true;
          Editor::Instance->Data().selectedPool_ = pool.poolName_;
          Editor::Instance->Data().selectedObject_ = std::string();

          ImGui::OpenPopup("Pool Popup");
        }
        else if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
        {
          itemClicked = true;
          Editor::Instance->Data().selectedPool_ = pool.poolName_;
          Editor::Instance->Data().selectedObject_ = std::string();
        }

        PoolPopupWidget::Use("Pool Popup");

        if (node_open)
        {
          for (auto jt = pool.objects_.begin(); jt != pool.objects_.end(); ++jt)
          {
            const std::string& objectName = *jt;

            ImGuiTreeNodeFlags object_tree_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

            if (objectName == Editor::Instance->Data().selectedObject_)
            {
              object_tree_flags |= ImGuiTreeNodeFlags_Selected;
            }

            ImGui::TreeNodeEx(objectName.c_str(), object_tree_flags);

            if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
            {
              itemClicked = true;
              Editor::Instance->Data().selectedPool_ = pool.poolName_;
              Editor::Instance->Data().selectedObject_ = objectName;

              ImGui::OpenPopup("Object Popup");
            }
            else if (ImGui::IsItemClicked())
            {
              itemClicked = true;
              Editor::Instance->Data().selectedPool_ = pool.poolName_;
              Editor::Instance->Data().selectedObject_ = objectName;
            }
          }

          ObjectPopupWidget::Use("Object Popup");

          ImGui::TreePop();
        }

        ImGui::Spacing();
        ImGui::PopID();
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
    }*/

    ImGui::End();
  }

  void HierarchyWidget::DeselectAll()
  {
    Editor::Instance->Data().selectedPool_ = std::string();
    Editor::Instance->Data().selectedObject_ = std::string();
  }
}