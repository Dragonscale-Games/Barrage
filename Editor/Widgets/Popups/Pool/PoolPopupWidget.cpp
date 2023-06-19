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
#include <Commands/Create/ComponentArray/CreateComponentArray.hpp>
#include <Commands/Create/Component/CreateComponent.hpp>
#include <Commands/Delete/Pool/DeletePool.hpp>
#include <Commands/Rename/Pool/RenamePool.hpp>

#include <Editor.hpp>

namespace Barrage
{
  void PoolPopupWidget::Use(const char* strId)
  {
    if (!ImGui::BeginPopup(strId))
    {
      return;
    }

    EditorData& editorData = Editor::Instance->Data();

    if (ImGui::Selectable("Create object"))
    {
      Editor::Instance->Command().Send(new CreateObject(editorData.selectedScene_, editorData.selectedPool_, true));
    }

    ImGui::Spacing();

    if (ImGui::Selectable("Create spawn archetype"))
    {
      Editor::Instance->Command().Send(new CreateObject(editorData.selectedScene_, editorData.selectedPool_, false));
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::Selectable("Add shared component"))
    {
      editorData.selectedComponent_ = std::string_view();
      editorData.openComponentModal_ = true;
    }

    ImGui::Spacing();

    if (ImGui::Selectable("Add component array"))
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
        Editor::Instance->Command().Send(new RenamePool(editorData.selectedScene_, editorData.selectedPool_, newName));
      };
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::Selectable("Delete"))
    {
      Editor::Instance->Command().Send(new DeletePool(editorData.selectedScene_, editorData.selectedPool_));
    }

    ImGui::EndPopup();
  }
}