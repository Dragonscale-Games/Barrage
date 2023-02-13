/* ======================================================================== */
/*!
 * \file            PoolPopupWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The menu that pops up when you right click a pool.
 */
 /* ======================================================================== */

#include "PoolPopupWidget.hpp"

#include <Commands/Create/Object/CreateObject.hpp>
#include <Commands/Create/ComponentArray/CreateComponentArray.hpp>
#include <Commands/Create/SharedComponent/CreateSharedComponent.hpp>
#include <Commands/Delete/Pool/DeletePool.hpp>

#include <Editor/Editor.hpp>

namespace Barrage
{
  void PoolPopupWidget::Use(const char* strId)
  {
    if (!ImGui::BeginPopup(strId))
    {
      return;
    }

    EditorData& editorData = Editor::Instance->Data();

    if (ImGui::Selectable("Create object"))
    {
      Editor::Instance->Command().Send(new CreateObject(editorData.selectedSpace_, editorData.selectedScene_, editorData.selectedPool_));
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::Selectable("Add shared component"))
    {
      editorData.selectedSharedComponent_ = std::string_view();
      editorData.openSharedComponentModal_ = true;
    }

    ImGui::Spacing();

    if (ImGui::Selectable("Add component array"))
    {
      editorData.selectedComponentArray_ = std::string_view();
      editorData.openComponentArrayModal_ = true;
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::Selectable("Delete pool"))
    {
      Editor::Instance->Command().Send(new DeletePool(editorData.selectedSpace_, editorData.selectedScene_, editorData.selectedPool_));
    }

    ImGui::EndPopup();
  }
}