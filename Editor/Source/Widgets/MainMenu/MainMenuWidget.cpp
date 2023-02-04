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

namespace Barrage
{
  MainMenuWidget::MainMenuWidget(EditorData& editorData, Engine& engine) :
    Widget(editorData, engine)
  {
  }

  void MainMenuWidget::UseWidget()
  {
    ImGui::BeginMainMenuBar();

    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("Exit"))
      {
        editorData_.isRunning_ = false;
      }
      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }
}