/* ======================================================================== */
/*!
 * \file            ComponentPopupWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The menu that pops up when you right click a component.
 */
 /* ======================================================================== */

#include "ComponentPopupWidget.hpp"

#include <Commands/Delete/Component/DeleteComponent.hpp>
#include <Editor.hpp>

namespace Barrage
{
  void ComponentPopupWidget::Use(const char* strId, const std::string_view& componentName)
  {
    if (!ImGui::BeginPopup(strId))
    {
      return;
    }

    if (ImGui::Selectable("Remove"))
    {
      EditorData& editorData = Editor::Instance->Data();
      Editor::Instance->Command().Send(new DeleteComponent(editorData.selectedScene_, editorData.selectedPool_, componentName));
    }

    ImGui::EndPopup();
  }
}