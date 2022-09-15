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
    Barrage::Engine::Instance = &engine_;

    engine_.Initialize();

    gui_.Initialize(engine_.Render().GetWindowHandle());

    Space* demo_space = Demo::CreateDemoSpace();

    engine_.Spaces().AddSpace("Demo Space", demo_space);
  }

  void Editor::Update()
  { 
    auto t1 = std::chrono::high_resolution_clock::now();
    
    engine_.Input().Update();

    gui_.StartWidgets();

    MakeTestWidget();

    gui_.EndWidgets();

    engine_.Render().StartFrame();

    engine_.Spaces().Update();
    engine_.Spaces().Draw();

    gui_.DrawWidgets();

    auto t2 = std::chrono::high_resolution_clock::now();

    engine_.Render().EndFrame();

    if (engine_.Render().WindowClosed())
      isRunning_ = false;

    engine_.Spaces().SetSpacePaused("Demo Space", statePaused_);

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    
    frameTime_ = duration.count();
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
    frametime = frametime + std::to_string(frameTime_) + " milliseconds";
    ImGui::Text(frametime.c_str());
    ImGui::Text("");

    ImGui::End();
  }
}