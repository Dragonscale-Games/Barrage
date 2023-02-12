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

    if (ImGui::Selectable("Create Object"))
    {
      EditorData& editorData = Editor::Instance->Data();
      Editor::Instance->Command().Send(new CreateObject(editorData.selectedSpace_, editorData.selectedScene_, editorData.selectedPool_));
    }

    ImGui::Separator();

    if (ImGui::Selectable("Delete Pool"))
    {
      EditorData& editorData = Editor::Instance->Data();
      Editor::Instance->Command().Send(new DeletePool(editorData.selectedSpace_, editorData.selectedScene_, editorData.selectedPool_));
    }

    ImGui::EndPopup();
  }
}