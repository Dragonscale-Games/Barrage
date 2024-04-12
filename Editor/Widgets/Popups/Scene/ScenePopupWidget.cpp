/* ======================================================================== */
/*!
 * \file            ScenePopupWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The menu that pops up when you right click a scene.
 */
 /* ======================================================================== */

#include "ScenePopupWidget.hpp"

#include <Commands/Create/Pool/CreatePool.hpp>
#include <Editor.hpp>

namespace Barrage
{
  void ScenePopupWidget::Use(const char* strId)
  {
    if (!ImGui::BeginPopup(strId))
    {
      return;
    }

    EditorData& editorData = Editor::Get().Data();

    if (ImGui::Selectable("Create pool"))
    {
      Editor::Get().Command().Send(std::make_shared<CreatePool>(editorData.selectedScene_));
    }

    /*ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::Selectable("Rename scene"))
    {
      editorData.openRenameModal_ = true;
      editorData.renameCallback_ = [](const std::string& newName)
      {
        EditorData& editorData = Editor::Get().Data();
        Editor::Get().Command().Send(new RenameScene(editorData.selectedScene_, newName));
      };
    }*/

    ImGui::EndPopup();
  }
}