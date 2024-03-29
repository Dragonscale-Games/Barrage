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
#include <Editor.hpp>
#include <Commands/Rename/Object/RenameObject.hpp>

namespace Barrage
{
  void ObjectPopupWidget::Use(const char* strId)
  {
    if (!ImGui::BeginPopup(strId))
    {
      return;
    }
    
    EditorData& editorData = Editor::Instance->Data();

    if (ImGui::Selectable("Add component"))
    {
      editorData.selectedComponentArray_ = std::string_view();
      editorData.openComponentArrayModal_ = true;
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::Selectable("Rename"))
    {
      editorData.openRenameModal_ = true;
      editorData.renameCallback_ = [](const std::string& newName)
      {
        EditorData& editorData = Editor::Instance->Data();
        Editor::Instance->Command().Send(new RenameObject(editorData.selectedScene_, editorData.selectedPool_, editorData.selectedObject_, newName));
      };
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::Selectable("Delete"))
    {
      Editor::Instance->Command().Send(new DeleteObject(editorData.selectedScene_, editorData.selectedPool_, editorData.selectedObject_));
    }

    ImGui::EndPopup();
  }
}