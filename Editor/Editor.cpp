/* ======================================================================== */
/*!
 * \file            Editor.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here>

 */
 /* ======================================================================== */

#include "stdafx.h"

#include "Editor.hpp"

#include <Widgets/Modals/Component/ComponentModal.hpp>
#include <Widgets/Modals/ComponentArray/ComponentArrayModal.hpp>
#include "Widgets/Modals/Project/ProjectModal.hpp"
#include <Widgets/Modals/Rename/RenameModal.hpp>
#include "Widgets/Modals/SaveProject/SaveProjectModal.hpp"
#include <Widgets/Modals/Tag/TagModal.hpp>

#include "Widgets/Windows/Game/GameWidget.hpp"
#include "Widgets/Windows/Hierarchy/HierarchyWidget.hpp"
#include "Widgets/Windows/Inspector/InspectorWidget.hpp"
#include "Widgets/Windows/Log/LogWidget.hpp"
#include "Widgets/Windows/Performance/PerformanceWidget.hpp"
#include "Widgets/Windows/Timeline/TimelineWidget.hpp"

#include "Widgets/MainMenu/MainMenuWidget.hpp"

#include <nfd.h>
#include <filesystem>
#include <fstream>

#include <Windows.h>

namespace Barrage
{
  Editor* Editor::instance_ = nullptr;
  
  Editor::Editor() :
    engine_(),
    commandQueue_(),
    data_(),
    gui_(),

    repeatTimer_(0),
    timeQueryID_(0)
  {
  }
  
  Editor& Editor::Get()
  {
    return *instance_;
  }
  
  void Editor::Run(const std::string& projectPath)
  {
    if (!data_.isRunning_)
    {
      data_.isRunning_ = true;

      Initialize(projectPath);

      while (data_.isRunning_)
      {
        Update();
      }

      Shutdown();

      data_.isRunning_ = false;
    }
  }

  CommandQueue& Editor::Command()
  {
    return commandQueue_;
  }
  
  EditorData& Editor::Data()
  {
    return data_;
  }

  GUI& Editor::Gui()
  {
    return gui_;
  }

  bool Editor::CreateProject(const std::string& name)
  {
    nfdchar_t* raw_path = NULL;
    nfdresult_t result = NFD_PickFolder(NULL, &raw_path);

    if (result != NFD_OKAY)
    {
      LogWidget::AddEntry("Could not create new project. (Problem selecting output folder.)");
      return false;
    }

    std::string directory(raw_path);
    free(raw_path);

    std::string project_folder_path = directory + "/" + name;

    if (std::filesystem::exists(project_folder_path))
    {
      LogWidget::AddEntry("Could not create new project. (Project folder already exists.)");
      return false;
    }

    std::filesystem::create_directory(project_folder_path);

    std::string project_file_path = project_folder_path + "/" + name + ".barproj";
    std::ofstream project_file(project_file_path);

    if (project_file.is_open())
    {
      project_file.close();
    }
    else
    {
      LogWidget::AddEntry("Could not create new project. (Problem creating project file.)");
      std::filesystem::remove_all(project_folder_path);
      return false;
    }

    if (!std::filesystem::create_directory(project_folder_path + "/Assets"))
    {
      LogWidget::AddEntry("Could not create new project. (Could not create Assets folder.)");
      std::filesystem::remove_all(project_folder_path);
      return false;
    }

    if (!std::filesystem::create_directory(project_folder_path + "/Assets/Scenes"))
    {
      LogWidget::AddEntry("Could not create new project. (Could not create Scenes folder.)");
      std::filesystem::remove_all(project_folder_path);
      return false;
    }

    if (!std::filesystem::create_directory(project_folder_path + "/Assets/Textures"))
    {
      LogWidget::AddEntry("Could not create new project. (Could not create Textures folder.)");
      std::filesystem::remove_all(project_folder_path);
      return false;
    }

    Entry entryFile;

    entryFile.AddSpace(Entry::SpaceEntry("Untitled", "Scene"));

    if (!Entry::SaveToFile(entryFile, project_folder_path + "/Assets/entry.json"))
    {
      LogWidget::AddEntry("Could not create new project. (Could not create entry file.)");
      std::filesystem::remove_all(project_folder_path);
      return false;
    }

    Scene untitled_scene("Scene");

    if (!Scene::SaveToFile(untitled_scene, project_folder_path + "/Assets/Scenes/Scene.scene"))
    {
      LogWidget::AddEntry("Could not create new project. (Could not create first scene.)");
      std::filesystem::remove_all(project_folder_path);
      return false;
    }

    if (!OpenProjectInternal(project_file_path))
    {
      LogWidget::AddEntry("Could not create new project. (Could not open project after creation.)");
      std::filesystem::remove_all(project_folder_path);
      return false;
    }

    LogWidget::AddEntry(std::string("\"" + name + "\" project created in \"" + directory + "\"."));

    return true;
  }

  bool Editor::OpenProject()
  {
    nfdchar_t* raw_path = NULL;
    nfdresult_t result = NFD_OpenDialog("barproj", NULL, &raw_path);

    if (result != NFD_OKAY)
    {
      LogWidget::AddEntry("Could not open project. (Problem selecting project file.)");
      return false;
    }

    std::string file_path(raw_path);
    free(raw_path);

    return OpenProjectInternal(file_path);
  }

  bool Editor::SaveProject(const std::string& directory)
  {
    std::string scenePath = directory + "/Assets/Scenes/Scene.scene";

    if (!std::filesystem::exists(scenePath))
    {
      LogWidget::AddEntry("Could not save project. (No scene file.)");
      return false;
    }

    Scene* scene = engine_.Scenes().GetScene("Scene");

    if (scene == nullptr || !Scene::SaveToFile(*scene, scenePath))
    {
      LogWidget::AddEntry("Could not save project. (Could not save scene.)");
      return false;
    }

    LogWidget::AddEntry("Saved project successfully.");
    data_.projectIsDirty_ = false;

    return true;
  }

  void Editor::Initialize(const std::string& projectPath)
  {
    instance_ = this;
    engine_.Initialize();
    gui_.Initialize(engine_.Window().GetWindowHandle());
    engine_.Window().Maximize();
    engine_.Frames().SetVsync(true);

    engine_.Spaces().AddSpace(data_.editorSpace_);
    Space* editorSpace = engine_.Spaces().GetSpace(data_.editorSpace_);
    editorSpace->AllowSceneChangesDuringUpdate(false);

    if (!OpenProjectInternal(projectPath))
    {
      LogWidget::Clear();
      data_.openProjectModal_ = true;
    }

    glGenQueries(1, &timeQueryID_);
  }

  void Editor::Update()
  {
    engine_.Frames().StartFrame();

    engine_.Input().Reset();
    engine_.Window().PollEvents();

    HandleKeyboard();

    unsigned numTicks = engine_.Frames().ConsumeTicks();

    TimePoint beginT;
    TimePoint endT;

    if (data_.gamePlaying_)
    {
      for (unsigned i = 0; i < numTicks; ++i)
      {
        beginT = std::chrono::high_resolution_clock::now();
        engine_.Spaces().Update();
        endT = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endT - beginT);
        PerformanceWidget::AddFrameSample(duration.count());
      }
    }

    commandQueue_.Process();

    if (data_.sceneIsDirty_)
    {
      Space* editorSpace = engine_.Spaces().GetSpace(data_.editorSpace_);

      editorSpace->SetScene(data_.selectedScene_);
      editorSpace->RNG().SetSeed(0xC0FFEEC0FFEE);

      for (unsigned i = 0; i < data_.gameTick_; ++i)
      {
        engine_.Spaces().Update();
      }

      data_.sceneIsDirty_ = false;
    }

    gui_.StartWidgets();
    UseWidgets();
    gui_.EndWidgets();

    glBeginQuery(GL_TIME_ELAPSED, timeQueryID_);
    engine_.Graphics().GetFramebuffer().BindFramebuffer();
    engine_.Graphics().ClearBackground();
    engine_.Spaces().Draw();
    engine_.Graphics().GetFramebuffer().UnbindFramebuffer();
    glEndQuery(GL_TIME_ELAPSED);
    gui_.DrawWidgets();
    engine_.Window().SwapBuffers();

    GLuint64 drawTimeNanoseconds;
    glGetQueryObjectui64v(timeQueryID_, GL_QUERY_RESULT, &drawTimeNanoseconds);
    long long drawSample = static_cast<long long>(drawTimeNanoseconds / 1000);
    PerformanceWidget::AddDrawSample(drawSample);

    if (engine_.Window().IsClosed())
    {
      glfwSetWindowShouldClose(engine_.Window().GetWindowHandle(), false);
      data_.isRunning_ = false;
    }

    if (!data_.isRunning_ && data_.projectIsDirty_)
    {
      data_.isRunning_ = true;
      data_.openSaveProjectModal_ = true;
    }

    engine_.Frames().EndFrame(!engine_.Window().IsFocused());
  }

  void Editor::Shutdown()
  {
    glDeleteQueries(1, &timeQueryID_);
    
    gui_.Shutdown();

    engine_.Shutdown();
    instance_ = nullptr;
  }

  void Editor::UseWidgets()
  {
    GameWidget::Use();
    MainMenuWidget::Use();
    HierarchyWidget::Use();
    InspectorWidget::Use();
    LogWidget::Use();
    PerformanceWidget::Use();
    TimelineWidget::Use();

    if (data_.openComponentModal_)
    {
      ImGui::OpenPopup("Add shared component");
      data_.openComponentModal_ = false;
    }

    if (data_.openComponentArrayModal_)
    {
      ImGui::OpenPopup("Add component array");
      data_.openComponentArrayModal_ = false;
    }

    if (data_.openTagModal_)
    {
      ImGui::OpenPopup("Add tag");
      data_.openTagModal_ = false;
    }

    if (data_.openRenameModal_)
    {
      ImGui::OpenPopup("Rename");
      data_.openRenameModal_ = false;
    }

    if (data_.openProjectModal_)
    {
      ImGui::OpenPopup("Project");
      data_.openProjectModal_ = false;
    }

    if (data_.openSaveProjectModal_)
    {
      ImGui::OpenPopup("Save Project");
      data_.openSaveProjectModal_ = false;
    }

    ComponentModal::Use("Add shared component");
    ComponentArrayModal::Use("Add component array");
    TagModal::Use("Add tag");
    RenameModal::Use("Rename", data_.renameCallback_);
    ProjectModal::Use("Project");
    SaveProjectModal::Use("Save Project");
  }

  void Editor::HandleKeyboard()
  {
    long long bigDelayMicroseconds = 500000;
    long long smallDelayMicroseconds = 100000;

    if (engine_.Input().KeyIsDown(GLFW_KEY_LEFT_CONTROL) && engine_.Input().KeyIsDown(GLFW_KEY_Z))
    {
      if (engine_.Input().KeyTriggered(GLFW_KEY_Z))
      {
        commandQueue_.Undo();
        repeatTimer_ = bigDelayMicroseconds;
      }
      else if (repeatTimer_ <= 0)
      {
        commandQueue_.Undo();
        repeatTimer_ = smallDelayMicroseconds;
      }
      else
      {
        repeatTimer_ -= engine_.Frames().DT();
      }
    }
    else if (engine_.Input().KeyIsDown(GLFW_KEY_LEFT_CONTROL) && engine_.Input().KeyIsDown(GLFW_KEY_Y))
    {
      if (engine_.Input().KeyTriggered(GLFW_KEY_Y))
      {
        commandQueue_.Redo();
        repeatTimer_ = bigDelayMicroseconds;
      }
      else if (repeatTimer_ <= 0)
      {
        commandQueue_.Redo();
        repeatTimer_ = smallDelayMicroseconds;
      }
      else
      {
        repeatTimer_ -= engine_.Frames().DT();
      }
    }

    if (engine_.Input().KeyTriggered(GLFW_KEY_F5))
    {
      BuildGame(true);
    }

    if (engine_.Input().KeyTriggered(GLFW_KEY_ESCAPE) && data_.gamePlaying_)
    {
      data_.gamePlaying_ = false;
      data_.sceneIsDirty_ = true;
    }
  }

  bool Editor::OpenProjectInternal(const std::string& path)
  {
    if (!std::filesystem::exists(path))
    {
      LogWidget::AddEntry("Could not open project. (Invalid path.)");
      return false;
    }

    std::filesystem::path filePath(path);

    if (filePath.extension() != ".barproj")
    {
      LogWidget::AddEntry("Could not open project. (Invalid project file type.)");
      return false;
    }

    std::string projectName(filePath.stem().string());
    std::string projectDirectory(filePath.parent_path().string());

    Scene scene = Scene::LoadFromFile(projectDirectory + "/Assets/Scenes/Scene.scene");
    std::string sceneName = scene.GetName();
    if (sceneName == "<untitled>")
    {
      LogWidget::AddEntry("Could not open project. (No scene file.)");
      return false;
    }

    std::filesystem::path textureDirectory(projectDirectory + "/Assets/Textures");

    engine_.Graphics().Textures().SetTextureDirectory(textureDirectory.string());
    engine_.Graphics().Textures().Clear();
    engine_.Scenes().Clear();
    engine_.Scenes().AddScene(sceneName, std::move(scene));
    data_.selectedScene_ = sceneName;
    engine_.Spaces().GetSpace(data_.editorSpace_)->SetScene(sceneName);

    if (std::filesystem::exists(textureDirectory))
    {
      for (const auto& entry : std::filesystem::directory_iterator(textureDirectory))
      {
        if (entry.path().extension() == ".png")
        {
          engine_.Graphics().Textures().LoadTexture(entry.path().stem().string());
        }
      }
    }

    data_.projectDirectory_ = projectDirectory;
    data_.projectName_ = projectName;
    data_.projectIsDirty_ = false;
    LogWidget::AddEntry("Opened project \"" + filePath.filename().string() + "\".");

    return true;
  }

  void Editor::BuildGame(bool runExecutable)
  {
    EditorData& editorData = Editor::Get().Data();
    std::string project_directory = editorData.projectDirectory_;
    std::string build_folder_name = "Build";
    std::string output_path = project_directory + "/" + build_folder_name;

    if (!std::filesystem::exists(project_directory + "/Assets"))
    {
      LogWidget::AddEntry("Could not build game. (No Assets folder.)");
      return;
    }

    if (!std::filesystem::exists("executable"))
    {
      LogWidget::AddEntry("Could not build game. (Could not locate executable to copy.)");
      return;
    }

    std::filesystem::remove_all(output_path);
    std::filesystem::create_directory(output_path);

    if (!std::filesystem::exists(output_path))
    {
      LogWidget::AddEntry("Could not build game. (Could not create build directory.)");
      return;
    }

    std::string executable_path = output_path + "/" + editorData.projectName_ + ".exe";
    std::filesystem::copy_file("executable", executable_path);

    for (auto const& dll_file : std::filesystem::directory_iterator{ "." })
    {
      if (dll_file.is_regular_file() && dll_file.path().extension() == ".dll")
      {
        std::filesystem::copy_file(dll_file, output_path + "/" + dll_file.path().filename().string());
      }
    }

    std::filesystem::copy(project_directory + "/Assets", output_path + "/Assets", std::filesystem::copy_options::recursive);

    LogWidget::AddEntry("Build succeeded.");

#ifdef _WIN64
    if (runExecutable && std::filesystem::exists(executable_path))
    {
      STARTUPINFO si;
      PROCESS_INFORMATION pi;

      ZeroMemory(&si, sizeof(si));
      si.cb = sizeof(si);
      ZeroMemory(&pi, sizeof(pi));

      // Start the child process. 
      if (!CreateProcess
      (
        executable_path.c_str(), // Module name
        NULL,                    // Command line
        NULL,                    // Process handle not inheritable
        NULL,                    // Thread handle not inheritable
        FALSE,                   // Set handle inheritance to FALSE
        0,                       // No creation flags
        NULL,                    // Environment block
        output_path.c_str(),     // Starting directory 
        &si,                     // Pointer to STARTUPINFO structure
        &pi                      // Pointer to PROCESS_INFORMATION structure
      )
        )
      {
        return;
      }

      // Close process and thread handles. 
      CloseHandle(pi.hProcess);
      CloseHandle(pi.hThread);
    }
#endif
  }
}