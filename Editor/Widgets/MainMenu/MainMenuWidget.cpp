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
#include "Editor.hpp"

#include "Widgets/Windows/Performance/PerformanceWidget.hpp"

namespace Barrage
{
  void MainMenuWidget::Use()
  {
    ImGui::BeginMainMenuBar();

    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("New project"))
      {
        Editor::Get().CreateProject("BulletGame");
      }

      ImGui::Spacing();

      if (ImGui::MenuItem("Open project"))
      {
        Editor::Get().OpenProject();
      }

      ImGui::Spacing();

      if (ImGui::MenuItem("Save project"))
      {
        Editor::Get().SaveProject(Editor::Get().Data().projectDirectory_);
      }

      ImGui::Spacing();
      ImGui::Separator();
      ImGui::Spacing();

      if (ImGui::MenuItem("Build"))
      {
        if (Editor::Get().SaveProject(Editor::Get().Data().projectDirectory_))
        {
          Editor::BuildGame();
        }
        else
        {
          LogWidget::AddEntry("Could not build game. (Error saving project before build.)");
        }
      }

      ImGui::Spacing();

      if (ImGui::MenuItem("Build and run"))
      {
        if (Editor::Get().SaveProject(Editor::Get().Data().projectDirectory_))
        {
          Editor::BuildGame(true);
        }
        else
        {
          LogWidget::AddEntry("Could not build game. (Error saving project before build.)");
        }
      }

      ImGui::Spacing();
      ImGui::Separator();
      ImGui::Spacing();
      
      if (ImGui::MenuItem("Exit"))
      {
        Editor::Get().Data().isRunning_ = false;
      }

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Edit"))
    {
      bool undoAvailable = Editor::Get().Command().UndoAvailable();

      if (!undoAvailable)
      {
        ImGui::BeginDisabled();
      }

      if (ImGui::MenuItem("Undo"))
      {
        Editor::Get().Command().Undo();
      }

      if (!undoAvailable)
      {
        ImGui::EndDisabled();
      }

      bool redoAvailable = Editor::Get().Command().RedoAvailable();

      if (!redoAvailable)
      {
        ImGui::BeginDisabled();
      }

      ImGui::Spacing();

      if (ImGui::MenuItem("Redo"))
      {
        Editor::Get().Command().Redo();
      }

      if (!redoAvailable)
      {
        ImGui::EndDisabled();
      }

      ImGui::EndMenu();
    }

    bool gamePlaying = Editor::Get().Data().gamePlaying_;

    if (ImGui::BeginMenu("Game"))
    {
      if (gamePlaying)
      {
        if (ImGui::MenuItem("Stop"))
        {
          Editor::Get().Data().gamePlaying_ = false;
          Editor::Get().Data().sceneIsDirty_ = true;
        }
      }
      else
      {
        if (ImGui::MenuItem("Play"))
        {
          Editor::Get().Data().gamePlaying_ = true;
          PerformanceWidget::Reset();
        }
      }

      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }
}