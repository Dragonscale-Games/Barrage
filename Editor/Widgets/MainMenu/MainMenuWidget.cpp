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
#include "Commands/Create/Pool/CreatePool.hpp"
#include "Commands/Create/Object/CreateObject.hpp"
#include "nfd.h"
#include <filesystem>
#include <Windows.h>
#include "Widgets/Windows/Performance/PerformanceWidget.hpp"

namespace Barrage
{
  ImVec2 MainMenuWidget::size_ = ImVec2(0.0f, 0.0f);
  
  void MainMenuWidget::Use()
  {
    ImGui::BeginMainMenuBar();

    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("New project"))
      {
        Editor::Instance->CreateProject("BulletGame");
      }
      
      ImGui::Spacing();

      if (ImGui::MenuItem("Open project"))
      {
        Editor::Instance->OpenProject();
      }

      ImGui::Spacing();

      if (ImGui::MenuItem("Save project"))
      {
        Editor::Instance->SaveProject(Editor::Instance->Data().projectDirectory_);
      }

      ImGui::Spacing();
      ImGui::Separator();
      ImGui::Spacing();

      if (ImGui::MenuItem("Import texture"))
      {
        ImportTexture();
      }

      ImGui::Spacing();
      ImGui::Separator();
      ImGui::Spacing();

      if (ImGui::MenuItem("Build"))
      {
        if (Editor::Instance->SaveProject(Editor::Instance->Data().projectDirectory_))
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
        if (Editor::Instance->SaveProject(Editor::Instance->Data().projectDirectory_))
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
        Editor::Instance->Data().isRunning_ = false;
      }

      ImGui::EndMenu();
    }

    size_ = ImGui::GetItemRectSize();

    if (ImGui::BeginMenu("Edit"))
    {
      bool undoAvailable = Editor::Instance->Command().UndoAvailable();
      
      if (!undoAvailable)
      {
        ImGui::BeginDisabled();
      }

      if (ImGui::MenuItem("Undo"))
      {
        Editor::Instance->Command().Undo();
      }

      if (!undoAvailable)
      {
        ImGui::EndDisabled();
      }

      bool redoAvailable = Editor::Instance->Command().RedoAvailable();

      if (!redoAvailable)
      {
        ImGui::BeginDisabled();
      }

      ImGui::Spacing();

      if (ImGui::MenuItem("Redo"))
      {
        Editor::Instance->Command().Redo();
      }

      if (!redoAvailable)
      {
        ImGui::EndDisabled();
      }

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Create"))
    {
      if (ImGui::MenuItem("Pool"))
      {
        std::string& scene = Editor::Instance->Data().selectedScene_;
        Editor::Instance->Command().Send(new CreatePool(scene));
      }

      if (Editor::Instance->Data().selectedPool_.empty())
      {
        ImGui::BeginDisabled();
      }

      ImGui::Spacing();

      if (ImGui::MenuItem("Object"))
      {
        std::string& scene = Editor::Instance->Data().selectedScene_;
        std::string& pool = Editor::Instance->Data().selectedPool_;
        Editor::Instance->Command().Send(new CreateObject(scene, pool, true));
      }

      ImGui::Spacing();

      if (ImGui::MenuItem("Spawn archetype"))
      {
        std::string& scene = Editor::Instance->Data().selectedScene_;
        std::string& pool = Editor::Instance->Data().selectedPool_;
        Editor::Instance->Command().Send(new CreateObject(scene, pool, false));
      }

      if (Editor::Instance->Data().selectedPool_.empty())
      {
        ImGui::EndDisabled();
      }

      ImGui::EndMenu();
    }

    bool gamePlaying = Editor::Instance->Data().gamePlaying_;

    if (ImGui::BeginMenu("Game"))
    {
      if (gamePlaying)
      {
        if (ImGui::MenuItem("Stop"))
        {
          Editor::Instance->Data().gamePlaying_ = false;
          Editor::Instance->Data().sceneIsDirty_ = true;
        }
      }
      else
      {
        if (ImGui::MenuItem("Play"))
        {
          Editor::Instance->Data().gamePlaying_ = true;
          PerformanceWidget::Reset();
        }
      }

      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }

  ImVec2 MainMenuWidget::GetSize()
  {
    return size_;
  }

  void MainMenuWidget::ImportTexture()
  {
    nfdchar_t* raw_path = NULL;
    nfdresult_t result = NFD_OpenDialog("png", NULL, &raw_path);

    if (result != NFD_OKAY)
    {
      LogWidget::AddEntry("Could not import texture. (Problem selecting texture file.)");
      return;
    }

    std::filesystem::path file_path(raw_path);
    free(raw_path);

    std::string texture_directory(Editor::Instance->Data().projectDirectory_ + "/Assets/Textures");

    if (!std::filesystem::exists(texture_directory))
    {
      LogWidget::AddEntry("Could not import texture. (No Textures folder in Assets folder.)");
      return;
    }

    if (file_path.extension() != ".png")
    {
      LogWidget::AddEntry("Could not import texture. (Invalid file type.)");
      return;
    }

    if (!std::filesystem::copy_file(file_path, texture_directory + "/" + file_path.filename().string()))
    {
      LogWidget::AddEntry("Could not import texture. (Could not copy file.)");
      return;
    }

    if (!Engine::Instance->Graphics().Textures().LoadTexture(file_path.stem().string()))
    {
      LogWidget::AddEntry("Error loading texture file after import.");
      return;
    }

    LogWidget::AddEntry("Imported texture file \"" + file_path.filename().string() + "\".");
  }
}