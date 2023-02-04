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

namespace Barrage
{
  HierarchyWidget::HierarchyWidget(EditorData& editorData, Engine& engine) :
    Widget(editorData, engine)
  {
  }

  void HierarchyWidget::UseWidget()
  {
    ImGui::Begin("Hierarchy");

    bool itemClicked = false;

    std::vector<PoolInfo>& pools = engine_.Scenes().GetScene("Demo Scene")->startingPools_;

    for (PoolInfo& pool : pools)
    {
      ImGuiTreeNodeFlags pool_tree_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

      if (pool.poolName_ == editorData_.selectedPool_)
      {
        pool_tree_flags |= ImGuiTreeNodeFlags_Selected;
      }

      bool node_open = ImGui::TreeNodeEx(pool.poolName_.data(), pool_tree_flags);

      if (ImGui::IsItemClicked())
      {
        itemClicked = true;
        editorData_.selectedPool_ = pool.poolName_;
        editorData_.selectedObject_ = std::string_view();
      }

      if (node_open)
      {
        for (std::string_view& objectName : pool.objects_)
        {
          ImGuiTreeNodeFlags object_tree_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

          if (objectName == editorData_.selectedObject_)
          {
            object_tree_flags |= ImGuiTreeNodeFlags_Selected;
          }

          ImGui::TreeNodeEx(objectName.data(), object_tree_flags);

          if (ImGui::IsItemClicked())
          {
            itemClicked = true;
            editorData_.selectedPool_ = pool.poolName_;
            editorData_.selectedObject_ = objectName;
          }
        }

        ImGui::TreePop();
      }
    }

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !itemClicked && ImGui::IsWindowHovered())
    {
      editorData_.selectedPool_ = std::string_view();
      editorData_.selectedObject_ = std::string_view();
    }

    ImGui::End();
  }
}