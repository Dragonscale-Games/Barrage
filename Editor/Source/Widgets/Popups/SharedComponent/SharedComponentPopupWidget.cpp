/* ======================================================================== */
/*!
 * \file            SharedComponentPopupWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The menu that pops up when you right click a shared component.
 */
 /* ======================================================================== */

#include "SharedComponentPopupWidget.hpp"

#include <Commands/Delete/SharedComponent/DeleteSharedComponent.hpp>
#include <Editor/Editor.hpp>

namespace Barrage
{
  void SharedComponentPopupWidget::Use(const char* strId, const std::string_view& componentName)
  {
    if (!ImGui::BeginPopup(strId))
    {
      return;
    }

    if (ImGui::Selectable("Remove"))
    {
      EditorData& editorData = Editor::Instance->Data();
      Editor::Instance->Command().Send(new DeleteSharedComponent(editorData.selectedSpace_, editorData.selectedPool_, componentName));
    }

    ImGui::EndPopup();
  }
}