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
  Editor::Editor() :
    engine_(),
    gui_(),
    data_(),
    isRunning_(false),

    hierarchy_(data_, engine_),
    inspector_(data_, engine_)
  {
  }

  void Editor::Run()
  {
    if (!isRunning_)
    {
      isRunning_ = true;
      
      Initialize();

      while (isRunning_)
      {
        Update();
      }

      Shutdown();

      isRunning_ = false;
    }
  }

  void Editor::Initialize()
  {
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

    engine_.Frames().SetFpsCap(FramerateController::FpsCap::FPS_120);
    engine_.Frames().SetVsync(false);
  }

  void Editor::Update()
  { 
    engine_.Frames().StartFrame();
    
    engine_.Input().Update();

    unsigned numTicks = engine_.Frames().ConsumeTicks();
    for (unsigned i = 0; i < numTicks; ++i)
    {
      engine_.Spaces().Update();
    }

    gui_.StartWidgets();
    UseEditorWidget();
    gui_.EndWidgets();

    Barrage::WindowManager& windowing = engine_.Windowing();
    Barrage::GfxDraw2D& drawing = engine_.Drawing();

    drawing.StartFrame();
    engine_.Spaces().Draw();
    drawing.RenderRequests();
    gui_.DrawWidgets();
    drawing.EndFrame();

    if(!windowing.IsOpen())
    {
      isRunning_ = false;
    }

    engine_.Frames().EndFrame();
  }

  void Editor::Shutdown()
  {
    gui_.Shutdown();
    
    engine_.Shutdown();
    
    Barrage::Engine::Instance = nullptr;
  }

  void Editor::UseEditorWidget()
  {
    hierarchy_.UseWidget();
    inspector_.UseWidget();

    ImGui::Begin("Placeholder");
    ImGui::End();
  }
}