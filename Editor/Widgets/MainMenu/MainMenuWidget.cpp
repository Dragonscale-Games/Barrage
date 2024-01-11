/* ======================================================================== */
/*!
 * \file            MainMenuWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The main menu bar that shows at the top of the screen.
 */
 /* ======================================================================== */

#include "MainMenuWidget.hpp"
#include <Editor.hpp>

namespace Barrage
{
  void MainMenuWidget::Use()
  {
    ImGui::BeginMainMenuBar();

    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("Exit"))
      {
        Editor::Get().isRunning_ = false;
      }

      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }
}