/* ======================================================================== */
/*!
 * \file            ObjectPopupWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The menu that pops up when you right click an object.
 */
 /* ======================================================================== */

#include "ObjectPopupWidget.hpp"

#include <Commands/Delete/Object/DeleteObject.hpp>
#include <Editor/Editor.hpp>

namespace Barrage
{
  void ObjectPopupWidget::Use(const char* strId)
  {
    if (!ImGui::BeginPopup(strId))
    {
      return;
    }

    if (ImGui::Selectable("Delete Object"))
    {
      EditorData& editorData = Editor::Instance->Data();
      Editor::Instance->Command().Send(new DeleteObject(editorData.selectedSpace_, editorData.selectedScene_, editorData.selectedPool_, editorData.selectedObject_));
    }

    ImGui::EndPopup();
  }
}