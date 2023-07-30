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
#include <Engine/Engine.hpp>

#include "Widgets/Windows/Hierarchy/HierarchyWidget.hpp"
#include "Widgets/Windows/Inspector/InspectorWidget.hpp"
#include "Widgets/MainMenu/MainMenuWidget.hpp"
#include "Widgets/Windows/Game/GameWidget.hpp"

#include <Widgets/Modals/Component/ComponentModal.hpp>
#include <Widgets/Modals/ComponentArray/ComponentArrayModal.hpp>
#include <Widgets/Modals/Tag/TagModal.hpp>
#include <Widgets/Modals/Rename/RenameModal.hpp>
#include <Widgets/Modals/Project/ProjectModal.hpp>

#include <unordered_set>
#include <chrono>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "nfd.h"

namespace Barrage
{
  Editor* Editor::Instance = nullptr;
  
  Editor::Editor() :
    engine_(),
    gui_(),
    data_(),

    repeatTimer_(0)
  {
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

  GUI& Editor::Gui()
  {
    return gui_;
  }

  EditorData& Editor::Data()
  {
    return data_;
  }

  CommandQueue& Editor::Command()
  {
    return commandQueue_;
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

    if (!Scene::SaveToFile(&untitled_scene, project_folder_path + "/Assets/Scenes/Scene.scene"))
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

    return Editor::Instance->OpenProjectInternal(file_path);
  }

  bool Editor::SaveProject(const std::string& directory)
  {
    std::string scenePath = directory + "/Assets/Scenes/Scene.scene";
    
    if (!std::filesystem::exists(scenePath))
    {
      LogWidget::AddEntry("Could not save project. (No scene file.)");
      return false;
    }

    if (!Scene::SaveToFile(engine_.Scenes().GetScene("Scene"), scenePath))
    {
      LogWidget::AddEntry("Could not save project. (Could not save scene.)");
      return false;
    }

    LogWidget::AddEntry("Saved project successfully.");
    return true;
  }

  void Editor::Initialize(const std::string& projectPath)
  {
    Instance = this;
    engine_.Initialize();
    gui_.Initialize(engine_.Window().GetWindowHandle());
    engine_.Window().Maximize();
    engine_.Frames().SetVsync(true);
    
    Space* editor_space = new Space;
    engine_.Spaces().AddSpace("Editor Space", editor_space);
    data_.selectedSpace_ = "Editor Space";
    
    if (!OpenProjectInternal(projectPath))
    {
      LogWidget::Clear();
      data_.openProjectModal_ = true;
    }
  }

  void Editor::Update()
  { 
    engine_.Frames().StartFrame();
    
    engine_.Input().Update();

    unsigned numTicks = engine_.Frames().ConsumeTicks();

    TimePoint beginT;
    TimePoint endT;

    if (data_.gamePlaying_)
    {
      for (unsigned i = 0; i < numTicks; ++i)
      {
        //beginT = std::chrono::high_resolution_clock::now();
        engine_.Spaces().Update();
        //endT = std::chrono::high_resolution_clock::now();
      }
    }

    commandQueue_.Process();

    if (data_.sceneIsDirty_)
    {
      //beginT = std::chrono::high_resolution_clock::now();
      engine_.Spaces().GetSpace(data_.selectedSpace_)->SetScene(data_.selectedScene_);
      data_.sceneIsDirty_ = false;
      //endT = std::chrono::high_resolution_clock::now();
      //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endT - beginT);
      //std::cout << "Scene set time: " << duration.count() << " microseconds" << std::endl;
    }

    //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endT - beginT);

    gui_.StartWidgets();
    /*ImGui::Begin("Time Test");
    ImGui::Text("Frame time (microseconds): ");
    ImGui::SameLine();
    ImGui::Text(numTicks ? std::to_string(duration.count()).c_str() : "0");
    ImGui::End();*/
    UseWidgets();
    gui_.EndWidgets();

    HandleKeyboard();

    engine_.Graphics().GetFramebuffer().BindFramebuffer();
    engine_.Graphics().ClearBackground();
    engine_.Spaces().Draw();
    engine_.Graphics().GetFramebuffer().UnbindFramebuffer();
    gui_.DrawWidgets();
    engine_.Window().SwapBuffers();
    
    if (engine_.Window().IsClosed())
    {
      data_.isRunning_ = false;
    }

    engine_.Frames().EndFrame();
  }

  void Editor::Shutdown()
  {
    gui_.Shutdown();
    
    engine_.Shutdown();
    Instance = nullptr;
  }

  void Editor::UseWidgets()
  {
    GameWidget::Use();
    
    bool gamePlaying = data_.gamePlaying_;
  
    MainMenuWidget::Use();
    HierarchyWidget::Use();
    InspectorWidget::Use();
    LogWidget::Use();

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

    ComponentModal::Use("Add shared component");
    ComponentArrayModal::Use("Add component array");
    TagModal::Use("Add tag");
    RenameModal::Use("Rename", data_.renameCallback_);
    ProjectModal::Use("Project");

    /*Barrage::GfxDraw2D& drawing = engine_.Drawing();
    Barrage::WindowManager& windowing = engine_.Windowing();

    WindowManager::WindowData window_settings = windowing.GetSettings();
    glm::ivec2 dimensions(0, 0);
    glm::ivec2 origin(0, 0);

    float x = window_settings.width_ - HierarchyWidget::GetSize().x - InspectorWidget::GetSize().x;
    float y = window_settings.height_ - LogWidget::GetSize().y - MainMenuWidget::GetSize().y;

    float adjusted_x = x;
    float adjusted_y = y;

    if (y != 0.0f && x / y > 16.0f / 9.0f)
    {
      adjusted_x = y * 16.0f / 9.0f;
    }
    else if (x != 0.0f && y / x > 9.0f / 16.0f)
    {
      adjusted_y = x * 9.0f / 16.0f;
    }

    dimensions.x = static_cast<int>(adjusted_x);
    dimensions.y = static_cast<int>(adjusted_y);

    if (dimensions.x <= 0)
    {
      dimensions.x = 1;
    }

    if (dimensions.y <= 0)
    {
      dimensions.y = 1;
    }

    origin.x = static_cast<int>(HierarchyWidget::GetSize().x + (x - adjusted_x) / 2.0f);
    origin.y = static_cast<int>(LogWidget::GetSize().y + (y - adjusted_y) / 2.0f);

    drawing.SetViewportSpace(dimensions, origin);*/
  }

  void Editor::HandleKeyboard()
  {
    long long bigDelayMicroseconds = 500000;
    long long smallDelayMicroseconds = 100000;
    
    if (engine_.Input().KeyIsDown(KEY_CTRL_LEFT) && engine_.Input().KeyIsDown(KEY_Z))
    {
      if (engine_.Input().KeyTriggered(KEY_Z))
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
    else if (engine_.Input().KeyIsDown(KEY_CTRL_LEFT) && engine_.Input().KeyIsDown(KEY_Y))
    {
      if (engine_.Input().KeyTriggered(KEY_Y))
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

    Scene* scene = Scene::LoadFromFile(projectDirectory + "/Assets/Scenes/Scene.scene");

    if (scene == nullptr)
    {
      LogWidget::AddEntry("Could not open project. (No scene file.)");
      return false;
    }

    std::filesystem::path textureDirectory(projectDirectory + "/Assets/Textures");

    engine_.Graphics().Textures().SetTextureDirectory(textureDirectory.string());
    engine_.Graphics().Textures().Clear();
    engine_.Scenes().Clear();
    engine_.Scenes().AddScene(scene);
    data_.selectedScene_ = scene->GetName();
    engine_.Spaces().GetSpace(data_.selectedSpace_)->SetScene(scene->GetName());

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

    LogWidget::AddEntry("Opened project \"" + filePath.filename().string() + "\".");

    return true;
  }
}