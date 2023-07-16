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