/* ======================================================================== */
/*!
 * \file            Engine.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The core engine class for a Barrage bullet hell game. Running this runs 
   the game.
 */
/* ======================================================================== */

#include "stdafx.h"
#include "Engine.hpp"
#include "Spaces/Space.hpp"

namespace Barrage
{
  Engine* Engine::Instance = nullptr;

  void Engine::Initialize()
  {
    Instance = this;
    
    renderer_.Initialize();
    inputManager_.Initialize(renderer_.GetWindowHandle());
    framerateController_.Initialize(renderer_.GetWindowHandle(), FramerateController::FpsCap::FPS_120, true);
  }

  void Engine::SetUpGame(Entry& entry)
  {
    for (auto it = entry.spaces_.begin(); it != entry.spaces_.end(); ++it)
    {
      Space* new_space = new Space;

      std::string scene_name = it->scene_;
      std::string scene_path = "./Assets/Scenes/" + scene_name + ".scene";

      Scene* new_scene = Scene::LoadFromFile(scene_path);

      if (new_scene)
      {
        Scenes().AddScene(new_scene);
        new_space->SetScene(scene_name);
      }

      Spaces().AddSpace(it->name_, new_space);
    }
  }

  void Engine::Shutdown()
  {
    inputManager_.Shutdown();
    renderer_.Shutdown();

    Instance = nullptr;
  }

  FramerateController& Engine::Frames()
  {
    return framerateController_;
  }

  InputManager& Engine::Input()
  {
    return inputManager_;
  }

  Renderer& Engine::Graphics()
  {
    return renderer_;
  }

  SceneManager& Engine::Scenes()
  {
    return sceneManager_;
  }

  SpaceManager& Engine::Spaces()
  {
    return spaceManager_;
  }

}