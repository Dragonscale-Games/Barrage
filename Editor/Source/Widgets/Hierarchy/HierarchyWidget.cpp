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

namespace Barrage
{
  HierarchyWidget::HierarchyWidget(EditorData& editorData, Engine& engine) :
    Widget(editorData, engine)
  {
  }

  void HierarchyWidget::UseWidget()
  {
    ImGui::Begin("Hierarchy");

    if (!editorData_.selectedScene_.empty())
    {
      ImGui::Separator();
      ImGui::Spacing();
      ImGui::Text(editorData_.selectedScene_.c_str());
      ImGui::Spacing();
      ImGui::Separator();
      ImGui::Spacing();

      bool itemClicked = false;

      const PoolInfoMap& pools = engine_.Scenes().GetScene(editorData_.selectedScene_)->startingPools_;

      for (auto it = pools.begin(); it != pools.end(); ++it)
      {
        const PoolInfo& pool = it->second;
        
        ImGuiTreeNodeFlags pool_tree_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

        if (pool.poolName_ == editorData_.selectedPool_)
        {
          pool_tree_flags |= ImGuiTreeNodeFlags_Selected;
        }

        std::string poolLabel = pool.poolName_.data();

        PoolArchetype* poolArchetype = engine_.Spaces().GetSpace(editorData_.selectedSpace_.data())->GetObjectManager().GetPoolArchetype(pool.poolName_);

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
        
        if (ImGui::IsItemClicked())
        {
          itemClicked = true;
          editorData_.selectedPool_ = pool.poolName_;
          editorData_.selectedObject_ = std::string();
        }

        if (node_open)
        {
          for (auto jt = pool.objects_.begin(); jt != pool.objects_.end(); ++jt)
          {
            const std::string& objectName = *jt;
            
            ImGuiTreeNodeFlags object_tree_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

            if (objectName == editorData_.selectedObject_)
            {
              object_tree_flags |= ImGuiTreeNodeFlags_Selected;
            }

            ImGui::TreeNodeEx(objectName.c_str(), object_tree_flags);

            if (ImGui::IsItemClicked())
            {
              itemClicked = true;
              editorData_.selectedPool_ = pool.poolName_;
              editorData_.selectedObject_ = objectName;
            }
          }

          ImGui::TreePop();
        }

        ImGui::Spacing();
      }

      if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !itemClicked && ImGui::IsWindowHovered())
      {
        editorData_.selectedPool_ = std::string();
        editorData_.selectedObject_ = std::string();
      }
    }

    ImGui::End();
  }
}