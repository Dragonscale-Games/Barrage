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
//#include "Objects/Systems/GameSystems.hpp"
#include "GS_DemoGame.hpp"
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

    engine_.GSM().SetGameState(Demo::GS_DemoGame());

    gui_.Initialize(Engine::Instance->Render().GetWindowHandle());
  }

  void Editor::Update()
  { 
    auto t1 = std::chrono::high_resolution_clock::now();
    
    engine_.Input().Update();

    gui_.StartWidgets();

    MakeTestWidget();

    gui_.EndWidgets();

    Engine::Instance->Render().StartFrame();

    if (!statePaused_)
    {
      if (engine_.GSM().GameStateIsRunning())
      {
        engine_.GSM().Update();
      }
      else
        isRunning_ = false;
    }

    engine_.Objects().Draw();

    gui_.DrawWidgets();

    auto t2 = std::chrono::high_resolution_clock::now();

    Engine::Instance->Render().EndFrame();

    if (Engine::Instance->Render().WindowClosed())
      isRunning_ = false;

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    
    frameTime_ = duration.count();
  }

  void Editor::Shutdown()
  {
    gui_.Shutdown();
    
    engine_.Instance->Shutdown();

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

    ImGui::Text("Currently registered:");
    ImGui::Text("----------------------");

    if (ImGui::CollapsingHeader("Pool Components"))
    {
      std::vector<std::string> pool_component_list = engine_.Objects().GetSharedComponentNames();

      for (auto it = pool_component_list.begin(); it != pool_component_list.end(); ++it)
      {
        ImGui::Text((*it).c_str());
      }

      ImGui::Text("");
    }
    
    if (ImGui::CollapsingHeader("Object Components"))
    {
      std::vector<std::string> object_component_list = engine_.Objects().GetComponentArrayNames();

      for (auto it = object_component_list.begin(); it != object_component_list.end(); ++it)
      {
        ImGui::Text((*it).c_str());
      }

      ImGui::Text("");
    }

    if (ImGui::CollapsingHeader("Initializers"))
    {
      std::vector<std::string> initializer_list = engine_.Objects().GetSpawnFuncNames();

      for (auto it = initializer_list.begin(); it != initializer_list.end(); ++it)
      {
        ImGui::Text((*it).c_str());
      }

      ImGui::Text("");
    }

    if (ImGui::CollapsingHeader("Systems"))
    {
      std::vector<std::string> registered_system_list = engine_.Objects().GetRegisteredSystemNames();
      std::vector<std::string> update_order_list = engine_.Objects().GetSystemUpdateOrder();
      std::vector<std::string> unused_system_list;

      std::unordered_set<std::string> used_system_set;

      used_system_set.insert(update_order_list.begin(), update_order_list.end());

      for (auto it = registered_system_list.begin(); it != registered_system_list.end(); ++it)
      {
        if (used_system_set.count(*it) == 0)
        {
          unused_system_list.push_back(*it);
        }
      }

      ImGui::Text("Update order:");
      ImGui::Text("--------------");

      for (auto it = update_order_list.begin(); it != update_order_list.end(); ++it)
      {
        ImGui::Text((*it).c_str());
      }
      
      ImGui::Text("");

      ImGui::Text("Non-updating systems:");
      ImGui::Text("----------------------");

      for (auto it = unused_system_list.begin(); it != unused_system_list.end(); ++it)
      {
        ImGui::Text((*it).c_str());
      }

      ImGui::Text("");
    }

    ImGui::Text("");
    ImGui::Text("Archetypes:");
    ImGui::Text("------------");

    if (ImGui::CollapsingHeader("Pool Archetypes"))
    {
      std::vector<std::string> archetype_list = engine_.Objects().GetPoolArchetypeNames();

      for (auto it = archetype_list.begin(); it != archetype_list.end(); ++it)
      {
        ImGui::Text((*it).c_str());
      }

      ImGui::Text("");
    }

    if (ImGui::CollapsingHeader("Object Archetypes"))
    {
      std::vector<std::string> archetype_list = engine_.Objects().GetObjectArchetypeNames();

      for (auto it = archetype_list.begin(); it != archetype_list.end(); ++it)
      {
        ImGui::Text((*it).c_str());
      }

      ImGui::Text("");
    }

    ImGui::Text("");
    ImGui::Text("Objects:");
    ImGui::Text("---------");

    if (ImGui::CollapsingHeader("Active Pools"))
    {
      std::vector<std::string> pool_list = engine_.Objects().GetPoolNames();

      for (auto it = pool_list.begin(); it != pool_list.end(); ++it)
      {
        ImGui::Text((*it).c_str());
      }

      ImGui::Text("");
    }

    ImGui::End();
  }
}