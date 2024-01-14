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
#include "Editor.hpp"

//#include <Commands/Delete/Object/DeleteObject.hpp>
//#include <Commands/Rename/Object/RenameObject.hpp>

namespace Barrage
{
  void ObjectPopupWidget::Use(const char* strId)
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
      /*editorData.openRenameModal_ = true;
      editorData.renameCallback_ = [](const std::string& newName)
      {
        EditorData& editorData = Editor::Instance->Data();
        Editor::Instance->Command().Send(new RenameObject(editorData.selectedScene_, editorData.selectedPool_, editorData.selectedObject_, newName));
      };*/
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::Selectable("Delete"))
    {
      /*Editor::Instance->Command().Send(new DeleteObject(editorData.selectedScene_, editorData.selectedPool_, editorData.selectedObject_));*/
    }

    ImGui::EndPopup();
  }
}