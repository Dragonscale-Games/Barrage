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

namespace Barrage
{
  ImVec2 MainMenuWidget::size_ = ImVec2(0.0f, 0.0f);
  
  void MainMenuWidget::Use()
  {
    ImGui::BeginMainMenuBar();

    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("Save scene"))
      {
        SaveScene();
      }
      
      if (ImGui::MenuItem("Load scene"))
      {
        LoadScene();
      }

      ImGui::Separator();

      if (ImGui::MenuItem("Build"))
      {
        BuildGame();
      }
      
      if (ImGui::MenuItem("Build and run"))
      {
        BuildGame(true);
      }

      ImGui::Separator();
      
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

      if (ImGui::MenuItem("Object"))
      {
        std::string& scene = Editor::Instance->Data().selectedScene_;
        std::string& pool = Editor::Instance->Data().selectedPool_;
        Editor::Instance->Command().Send(new CreateObject(scene, pool, true));
      }

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

    if (gamePlaying)
    {
      ImGui::EndDisabled();
    }

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
        }
      }

      ImGui::EndMenu();
    }

    if (gamePlaying)
    {
      ImGui::BeginDisabled();
    }

    ImGui::EndMainMenuBar();
  }

  ImVec2 MainMenuWidget::GetSize()
  {
    return size_;
  }

  void MainMenuWidget::SaveScene()
  {
    nfdchar_t* raw_path = NULL;
    nfdresult_t result = NFD_SaveDialog(NULL, NULL, &raw_path);
    
    if (result != NFD_OKAY)
    {
      LogWidget::AddEntry("Could not save scene.");
      return;
    }
    
    std::string path(raw_path);
    free(raw_path);
    
    EditorData& editorData = Editor::Instance->Data();
    Scene* scene = Engine::Instance->Scenes().GetScene(editorData.selectedScene_);

    if (scene == nullptr)
    {
      LogWidget::AddEntry("Could not save scene.");
      return;
    }

    if (Scene::SaveToFile(scene, path))
    {
      LogWidget::AddEntry("Saved scene to \"" + path + "\".");
    }
    else
    {
      LogWidget::AddEntry("Could not save scene.");
    }
  }

  void MainMenuWidget::LoadScene()
  {
    nfdchar_t* raw_path = NULL;
    nfdresult_t result = NFD_OpenDialog(NULL, NULL, &raw_path);

    if (result != NFD_OKAY)
    {
      LogWidget::AddEntry("Could not load scene.");
      return;
    }

    std::string path(raw_path);
    free(raw_path);
    
    EditorData& editorData = Editor::Instance->Data();
    Scene* scene = Scene::LoadFromFile(path);
    
    if (scene == nullptr)
    {
      LogWidget::AddEntry("Could not load scene.");
    }
    else
    {
      LogWidget::AddEntry("Loaded scene from \"" + path + "\".");
      editorData.nextScene_ = scene;
    }
  }

  void MainMenuWidget::BuildGame(bool runExecutable)
  {
    nfdchar_t* raw_path = NULL;
    nfdresult_t result = NFD_PickFolder(NULL, &raw_path);

    if (result != NFD_OKAY)
    {
      LogWidget::AddEntry("Could not build game. (Problem selecting output folder.)");
      return;
    }

    std::string output_path(raw_path);
    free(raw_path);

    std::string build_folder_name = "build";
    output_path += "/" + build_folder_name + "/";

    LogWidget::AddEntry("Chose output path %s", output_path.c_str());

    if (std::filesystem::exists(output_path))
    {
      LogWidget::AddEntry("Could not build game. (Output directory already contains \"build\" folder.)");
      return;
    }

    if (!std::filesystem::exists("executable"))
    {
      LogWidget::AddEntry("Could not build game. (Could not locate executable to copy.)");
      return;
    }

    std::vector<std::string> texture_names = Engine::Instance->GfxRegistry().GetTextureNames();

    for (const auto& texture_name : texture_names)
    {
      std::string texture_path = "Assets/Textures/" + texture_name + ".png";
      
      if (!std::filesystem::exists(texture_path))
      {
        LogWidget::AddEntry("Could not build game. (Texture does not exist at %s.)", texture_path.c_str());
        return;
      }
    }

    std::filesystem::create_directory(output_path);

    if (!std::filesystem::exists(output_path))
    {
      LogWidget::AddEntry("Could not build game. (Could not create build directory.)");
      return;
    }

    std::string executable_path = output_path + "Game.exe";
    std::filesystem::copy_file("executable", executable_path);

    for (auto const& dll_file : std::filesystem::directory_iterator{ "." })
    {
      if (dll_file.is_regular_file() && dll_file.path().extension() == ".dll")
      {
        std::filesystem::copy_file(dll_file, output_path + dll_file.path().filename().string());
      }
    }

    std::filesystem::copy("Assets", output_path + "Assets", std::filesystem::copy_options::recursive);

    if (runExecutable && std::filesystem::exists(executable_path))
    {
      STARTUPINFO si;
      PROCESS_INFORMATION pi;

      ZeroMemory(&si, sizeof(si));
      si.cb = sizeof(si);
      ZeroMemory(&pi, sizeof(pi));

      // Start the child process. 
      if (!CreateProcess(executable_path.c_str(), // Module name
        NULL,           // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi)            // Pointer to PROCESS_INFORMATION structure
        )
      {
        return;
      }

      // Close process and thread handles. 
      CloseHandle(pi.hProcess);
      CloseHandle(pi.hThread);
    }
  }
}