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

//#include <Commands/Create/Pool/CreatePool.hpp>
//#include <Commands/Rename/Scene/RenameScene.hpp>
#include <Editor.hpp>

namespace Barrage
{
  void ScenePopupWidget::Use(const char* strId)
  {
    if (!ImGui::BeginPopup(strId))
    {
      return;
    }

    //EditorData& editorData = Editor::Get().Data();

    if (ImGui::Selectable("Create pool"))
    {
      //Editor::Instance->Command().Send(new CreatePool(editorData.selectedScene_));
    }

    /*ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::Selectable("Rename scene"))
    {
      editorData.openRenameModal_ = true;
      editorData.renameCallback_ = [](const std::string& newName)
      {
        EditorData& editorData = Editor::Instance->Data();
        Editor::Instance->Command().Send(new RenameScene(editorData.selectedScene_, newName));
      };
    }*/

    ImGui::EndPopup();
  }
}