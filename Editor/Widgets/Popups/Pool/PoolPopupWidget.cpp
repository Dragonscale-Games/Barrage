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

#include <Commands/Create/StartingObject/CreateStartingObject.hpp>
#include <Commands/Create/SpawnArchetype/CreateSpawnArchetype.hpp>
#include <Commands/Create/ComponentArray/CreateComponentArray.hpp>
#include <Commands/Create/Component/CreateComponent.hpp>
#include <Commands/Delete/Pool/DeletePool.hpp>
#include <Commands/Rename/Pool/RenamePool.hpp>
#include <Commands/Duplicate/Pool/DuplicatePool.hpp>

#include <Editor.hpp>

namespace Barrage
{
  void PoolPopupWidget::Use(const char* strId)
  {
    if (!ImGui::BeginPopup(strId))
    {
      return;
    }

    EditorData& editorData = Editor::Get().Data();

    if (ImGui::Selectable("Create object"))
    {
      Editor::Get().Command().Send(std::make_shared<CreateStartingObject>(editorData.selectedScene_, editorData.selectedPool_));
    }

    ImGui::Spacing();

    if (ImGui::Selectable("Create spawn archetype"))
    {
      Editor::Get().Command().Send(std::make_shared<CreateSpawnArchetype>(editorData.selectedScene_, editorData.selectedPool_));
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::Selectable("Add component to pool"))
    {
      editorData.selectedComponent_ = std::string();
      editorData.openComponentModal_ = true;
    }

    ImGui::Spacing();

    if (ImGui::Selectable("Add component to objects"))
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
        Editor::Get().Command().Send(std::make_shared<RenamePool>(editorData.selectedScene_, editorData.selectedPool_, newName));
      };
    }

    ImGui::Spacing();
    
    if (ImGui::Selectable("Duplicate"))
    {
      Editor::Get().Command().Send(std::make_shared<DuplicatePool>(editorData.selectedScene_, editorData.selectedPool_));
    }

    ImGui::Spacing();

    if (ImGui::Selectable("Delete"))
    {
      Editor::Get().Command().Send(std::make_shared<DeletePool>(editorData.selectedScene_, editorData.selectedPool_));
    }

    ImGui::EndPopup();
  }
}