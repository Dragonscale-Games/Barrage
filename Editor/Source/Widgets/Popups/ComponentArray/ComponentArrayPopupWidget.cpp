/* ======================================================================== */
/*!
 * \file            ComponentArrayPopupWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The menu that pops up when you right click a component array.
 */
 /* ======================================================================== */

#include "ComponentArrayPopupWidget.hpp"

#include <Commands/Delete/ComponentArray/DeleteComponentArray.hpp>
#include <Editor/Editor.hpp>

namespace Barrage
{
  void ComponentArrayPopupWidget::Use(const char* strId, const std::string_view& componentArrayName)
  {
    if (!ImGui::BeginPopup(strId))
    {
      return;
    }

    if (ImGui::Selectable("Remove"))
    {
      EditorData& editorData = Editor::Instance->Data();
      Editor::Instance->Command().Send(new DeleteComponentArray(editorData.selectedScene_, editorData.selectedPool_, componentArrayName));
    }

    ImGui::EndPopup();
  }
}