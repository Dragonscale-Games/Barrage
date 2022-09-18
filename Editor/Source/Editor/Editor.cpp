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
    frameTime_(),
    numTicks_(0),
    statePaused_(false),
    isRunning_(false)
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
    Barrage::GfxRegistry2D& registry = engine_.Registry();
    Barrage::GfxDraw2D& drawing = engine_.Drawing();

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
    // Set the viewport of our game.
    const Barrage::WindowManager::WindowData& settings = windowing.GetSettings();
    drawing.SetViewportSpace(glm::ivec2(settings.width_, settings.height_));

    gui_.Initialize(windowing.GetInternalHandle());

    Space* demo_space = Demo::CreateDemoSpace();
    engine_.Spaces().AddSpace("Demo Space", demo_space);
  }

  void Editor::Update()
  { 
    engine_.Frames().StartFrame();
    
    engine_.Input().Update();

    numTicks_ = engine_.Frames().ConsumeTicks();
    for (unsigned i = 0; i < numTicks_; ++i)
    {
      engine_.Spaces().Update();
    }

    gui_.StartWidgets();
    MakeTestWidget();
    gui_.EndWidgets();

    Barrage::WindowManager& windowing = engine_.Windowing();
    Barrage::GfxDraw2D& drawing = engine_.Drawing();

    drawing.StartFrame();
    engine_.Spaces().Draw();
    gui_.DrawWidgets();
    drawing.EndFrame();

    if(!windowing.IsOpen())
    {
      isRunning_ = false;
    }
      
    engine_.Spaces().SetSpacePaused("Demo Space", statePaused_);

    engine_.Frames().EndFrame();
    frameTime_ = engine_.Frames().DT();
  }

  void Editor::Shutdown()
  {
    gui_.Shutdown();
    
    engine_.Shutdown();

    Barrage::Engine::Instance = nullptr;
  }

  void Editor::MakeTestWidget()
  {
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 20, main_viewport->WorkPos.y + 20), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(240, 680), ImGuiCond_Once);

    ImGui::Begin("Editor");

    ImGui::Checkbox("Pause game", &statePaused_);
    ImGui::Text("");
    
    std::string frametime("Frame time: ");
    frametime = frametime + std::to_string(frameTime_) + " microseconds";
    ImGui::Text(frametime.c_str());
    ImGui::Text("");

    double fps;

    if (frameTime_ > 0)
      fps = 1000000.0 / static_cast<double>(frameTime_);
    else
      fps = 0.0;

    std::string fpstime("FPS: ");
    fpstime = fpstime + std::to_string(fps);
    ImGui::Text(fpstime.c_str());
    ImGui::Text("");

    std::string ticksdisplay("Number of ticks per frame: ");
    ticksdisplay = ticksdisplay + std::to_string(numTicks_);
    ImGui::Text(ticksdisplay.c_str());
    ImGui::Text("");

    if (ImGui::Button("60 fps"))
    {
      engine_.Frames().SetFpsCap(FramerateController::FpsCap::FPS_60);
    }

    if (ImGui::Button("120 fps"))
    {
      engine_.Frames().SetFpsCap(FramerateController::FpsCap::FPS_120);
    }

    if (ImGui::Button("No cap"))
    {
      engine_.Frames().SetFpsCap(FramerateController::FpsCap::NO_CAP);
    }

    ImGui::Text("");

    if (ImGui::Button("Enable vsync"))
    {
      engine_.Frames().SetVsync(true);
    }
    ImGui::SameLine();
    if (ImGui::Button("Disable vsync"))
    {
      engine_.Frames().SetVsync(false);
    }
    
    ImGui::End();
  }
}