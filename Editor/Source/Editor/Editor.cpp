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
    Barrage::GfxRegistry2D& registry = engine_.GfxRegistry();
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

    engine_.Frames().SetFpsCap(FramerateController::FpsCap::FPS_120);
    engine_.Frames().SetVsync(false);
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
    drawing.RenderRequests();
    gui_.DrawWidgets();
    drawing.EndFrame();

    if(!windowing.IsOpen())
    {
      isRunning_ = false;
    }

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

    ObjectManager& object_manager = engine_.Spaces().GetSpace("Demo Space")->GetObjectManager();
    std::vector<std::string_view> pool_archetype_names = object_manager.GetPoolArchetypeNames();

    for (auto it = pool_archetype_names.begin(); it != pool_archetype_names.end(); ++it)
    {
      PoolArchetype* pool_archetype = object_manager.GetPoolArchetype(*it);

      ImGui::Text(it->data());
      ImGui::Text("");
      ImGui::Text("Shared components:");
      ImGui::Text("-------------------");
      for (auto jt = pool_archetype->sharedComponents_.begin(); jt != pool_archetype->sharedComponents_.end(); ++jt)
      {
        if (ImGui::CollapsingHeader(jt->first.data()))
        {
          rttr::type component_type = rttr::type::get_by_name(jt->first.data());

          if (component_type.is_valid())
          {
            for (auto& prop : component_type.get_properties())
            {
              ImGui::Text(prop.get_name().data());
            }
          }
        }
      }

      ImGui::Text("");
      ImGui::Text("Component arrays:");
      ImGui::Text("------------------");
      for (auto jt = pool_archetype->componentArrayNames_.begin(); jt != pool_archetype->componentArrayNames_.end(); ++jt)
      {
        ImGui::Text(jt->data());
      }

      ImGui::Text("");
      ImGui::Text("Tags:");
      ImGui::Text("------");
      for (auto jt = pool_archetype->tags_.begin(); jt != pool_archetype->tags_.end(); ++jt)
      {
        ImGui::Text(jt->data());
      }
      ImGui::Text("");
    }
    
    ImGui::End();
  }
}