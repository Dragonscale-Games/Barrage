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
#include <Editor/Editor.hpp>
#include "Commands/CreatePool/CreatePool.hpp"

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

    if (ImGui::BeginMenu("Edit"))
    {
      if (ImGui::MenuItem("Undo"))
      {
        Editor::Instance->Command().Undo();
      }

      if (ImGui::MenuItem("Redo"))
      {
        Editor::Instance->Command().Redo();
      }

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Create"))
    {
      if (ImGui::MenuItem("Pool"))
      {
        std::string& space = Editor::Instance->Data().selectedSpace_;
        std::string& scene = Editor::Instance->Data().selectedScene_;
        Editor::Instance->Command().Add(new CreatePool(space, scene));
      }

      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }
}