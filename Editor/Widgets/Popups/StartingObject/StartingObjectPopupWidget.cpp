/* ======================================================================== */
/*!
 * \file            StartingObjectPopupWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The menu that pops up when you right click a starting object.
 */
 /* ======================================================================== */

#include "StartingObjectPopupWidget.hpp"
#include "Editor.hpp"

#include <Commands/Delete/StartingObject/DeleteStartingObject.hpp>
#include <Commands/Rename/StartingObject/RenameStartingObject.hpp>

namespace Barrage
{
  void StartingObjectPopupWidget::Use(const char* strId)
  {
    if (!ImGui::BeginPopup(strId))
    {
      return;
    }
    
    EditorData& editorData = Editor::Get().Data();

    if (ImGui::Selectable("Add component to pool"))
    {
      editorData.selectedComponent_ = std::string();
      editorData.openComponentModal_ = true;
    }

    ImGui::Spacing();

    if (ImGui::Selectable("Add component to object"))
    {
      editorData.selectedComponentArray_ = std::string();
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
        EditorData& editorData = Editor::Get().Data();
        Editor::Get().Command().Send(std::make_shared<RenameStartingObject>(
          editorData.selectedScene_, 
          editorData.selectedPool_, 
          editorData.selectedStartingObject_, 
          newName
        ));
      };
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::Selectable("Delete"))
    {
      Editor::Get().Command().Send(std::make_shared<DeleteStartingObject>(
        editorData.selectedScene_, 
        editorData.selectedPool_, 
        editorData.selectedStartingObject_
      ));
    }

    ImGui::EndPopup();
  }
}