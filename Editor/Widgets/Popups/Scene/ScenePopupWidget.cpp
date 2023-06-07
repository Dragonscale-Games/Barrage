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

    if (ImGui::Selectable("Create pool"))
    {
      EditorData& editorData = Editor::Instance->Data();
      Editor::Instance->Command().Send(new CreatePool(editorData.selectedScene_));
    }

    ImGui::EndPopup();
  }
}