/* ======================================================================== */
/*!
 * \file            SpawnArchetypePopupWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The menu that pops up when you right click a spawn archetype.
 */
 /* ======================================================================== */

#include "SpawnArchetypePopupWidget.hpp"
#include "Editor.hpp"

#include <Commands/Delete/SpawnArchetype/DeleteSpawnArchetype.hpp>
#include <Commands/Rename/SpawnArchetype/RenameSpawnArchetype.hpp>

namespace Barrage
{
  void SpawnArchetypePopupWidget::Use(const char* strId)
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

    if (ImGui::Selectable("Add component to spawn archetype"))
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
        Editor::Get().Command().Send(std::make_shared<RenameSpawnArchetype>(
          editorData.selectedScene_, 
          editorData.selectedPool_, 
          editorData.selectedSpawnArchetype_,
          newName
        ));
      };
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::Selectable("Delete"))
    {
      Editor::Get().Command().Send(std::make_shared<DeleteSpawnArchetype>(
        editorData.selectedScene_, 
        editorData.selectedPool_, 
        editorData.selectedSpawnArchetype_
      ));
    }

    ImGui::EndPopup();
  }
}