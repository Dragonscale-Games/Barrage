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

#include <Widgets/Modals/Component/ComponentModal.hpp>
#include <Widgets/Modals/ComponentArray/ComponentArrayModal.hpp>

#include <unordered_set>
#include <chrono>
#include <iostream>
#include <filesystem>

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

  void Editor::Run()
  {
    if (!data_.isRunning_)
    {
      data_.isRunning_ = true;
      
      Initialize();

      while (data_.isRunning_)
      {
        Update();
      }

      Shutdown();

      data_.isRunning_ = false;
    }
  }

  EditorData& Editor::Data()
  {
    return data_;
  }

  CommandQueue& Editor::Command()
  {
    return commandQueue_;
  }

  void Editor::Initialize()
  {
    Instance = this;
    engine_.Initialize();

    Barrage::WindowManager& windowing = engine_.Windowing();
    Barrage::GfxRegistry2D& registry = engine_.GfxRegistry();
    Barrage::GfxDraw2D& drawing = engine_.Drawing();

    windowing.ChangeTitle("Barrage Editor");

    // Register the assets necessary.
    const char* instancedShaderPaths[] = {
      "Assets/Shaders/Instanced.vs",
      "Assets/Shaders/Instanced.fs",
    };
    registry.RegisterShader(instancedShaderPaths, "Instanced");
    drawing.ApplyShader("Instanced");

    for (auto const& texture_file : std::filesystem::directory_iterator{ "Assets/Textures" })
    {
      if (texture_file.is_regular_file() && texture_file.path().extension() == ".png")
      {
        registry.RegisterTexture(texture_file.path().string().c_str(), texture_file.path().stem().string().c_str());
      }
    }
    
    // Set the viewport of our game
    const Barrage::WindowManager::WindowData& settings = windowing.GetSettings();
    drawing.SetViewportSpace(glm::ivec2(settings.width_, settings.height_));

    gui_.Initialize(windowing.GetInternalHandle());

    Space* main_space = new Space;
    Scene* demo_scene = new Scene("Demo Scene");
    engine_.Scenes().AddScene(demo_scene);
    main_space->SetScene("Demo Scene");
    engine_.Spaces().AddSpace("Main Space", main_space);
    data_.selectedScene_ = "Demo Scene";
    data_.selectedSpace_ = "Main Space";
    engine_.Frames().SetVsync(true);

    float zoom = 1.0f;
    float angle = 0.0f;
    glm::vec2 position(0.0f);

    engine_.Drawing().SetCameraTransform(position, zoom, angle);
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

    if (data_.nextScene_)
    {
      ChangeScene();
    }

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

    Barrage::WindowManager& windowing = engine_.Windowing();
    Barrage::GfxDraw2D& drawing = engine_.Drawing();

    drawing.StartFrame();
    engine_.Spaces().Draw();
    drawing.RenderRequests();
    gui_.DrawWidgets();
    drawing.EndFrame();

    if (!windowing.IsOpen())
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
    bool gamePlaying = data_.gamePlaying_;
    
    if (gamePlaying)
    {
      ImGui::BeginDisabled();
    }
    
    MainMenuWidget::Use();
    HierarchyWidget::Use();
    InspectorWidget::Use();
    ImGui::ShowDemoWindow();
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

    ComponentModal::Use("Add shared component");
    ComponentArrayModal::Use("Add component array");

    if (gamePlaying)
    {
      ImGui::EndDisabled();
    }

    Barrage::GfxDraw2D& drawing = engine_.Drawing();
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

    origin.x = static_cast<int>(HierarchyWidget::GetSize().x + (x - adjusted_x) / 2.0f);
    origin.y = static_cast<int>(LogWidget::GetSize().y + (y - adjusted_y) / 2.0f);

    drawing.SetViewportSpace(dimensions, origin);
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

  void Editor::ChangeScene()
  {
    Scene* scene = data_.nextScene_;
    
    if (scene == nullptr)
    {
      return;
    }

    engine_.Scenes().AddScene(scene);
    data_.selectedScene_ = scene->GetName();
    data_.nextScene_ = nullptr;
    data_.sceneIsDirty_ = true;
  }
}