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
#include <DemoInitialization.hpp>
#include <Engine/Engine.hpp>

#include <unordered_set>
#include <chrono>

namespace Barrage
{
  Editor* Editor::Instance = nullptr;
  
  Editor::Editor() :
    engine_(),
    gui_(),
    data_(),

    hierarchy_(data_, engine_),
    inspector_(data_, engine_),
    log_(data_, engine_),
    mainMenu_(data_, engine_),

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

  LogWidget& Editor::Log()
  {
    return log_;
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
      "Assets/Shaders/Default/Instanced.vs",
      "Assets/Shaders/Default/Instanced.fs",
    };
    registry.RegisterShader(instancedShaderPaths, "Instanced");
    registry.RegisterTexture("Assets/Textures/TestBullet.png", "TestBullet");
    registry.RegisterTexture("Assets/Textures/TestShip.png", "TestShip");
    // Set any default resources on the draw system.
    drawing.ApplyShader("Instanced");
    // Set the viewport of our game
    const Barrage::WindowManager::WindowData& settings = windowing.GetSettings();
    drawing.SetViewportSpace(glm::ivec2(settings.width_, settings.height_));

    gui_.Initialize(windowing.GetInternalHandle());

    Space* demo_space = Demo::CreateDemoSpace();
    engine_.Spaces().AddSpace("Demo Space", demo_space);
    data_.selectedScene_ = "Demo Scene";
    data_.selectedSpace_ = "Demo Space";
    engine_.Frames().SetVsync(true);
  }

  void Editor::Update()
  { 
    engine_.Frames().StartFrame();
    
    engine_.Input().Update();

    unsigned numTicks = engine_.Frames().ConsumeTicks();

    if (data_.gamePlaying_)
    {
      for (unsigned i = 0; i < numTicks; ++i)
      {
        //engine_.Spaces().Update();
      }
    }
    
    commandQueue_.Process();

    if (data_.sceneIsDirty_)
    {
      engine_.Spaces().GetSpace(data_.selectedSpace_)->SetScene(data_.selectedScene_);
      data_.sceneIsDirty_ = false;
    }

    gui_.StartWidgets();
    UseEditorWidget();
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

  void Editor::UseEditorWidget()
  {
    mainMenu_.UseWidget();
    hierarchy_.UseWidget();
    inspector_.UseWidget();
    ImGui::ShowDemoWindow();
    log_.UseWidget();
  }

  void Editor::HandleKeyboard()
  {
    long long bigDelayMilliseconds = 500000;
    long long smallDelayMilliseconds = 100000;
    
    if (engine_.Input().KeyIsDown(KEY_CTRL_LEFT) && engine_.Input().KeyIsDown(KEY_Z))
    {
      if (engine_.Input().KeyTriggered(KEY_Z))
      {
        commandQueue_.Undo();
        repeatTimer_ = bigDelayMilliseconds;
      }
      else if (repeatTimer_ <= 0)
      {
        commandQueue_.Undo();
        repeatTimer_ = smallDelayMilliseconds;
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
        repeatTimer_ = bigDelayMilliseconds;
      }
      else if (repeatTimer_ <= 0)
      {
        commandQueue_.Redo();
        repeatTimer_ = smallDelayMilliseconds;
      }
      else
      {
        repeatTimer_ -= engine_.Frames().DT();
      }
    }
  }
}