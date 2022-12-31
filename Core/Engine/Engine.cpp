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

  Engine::Engine() :
    framerateController_(),
    inputManager_(),
    spaceManager_()
  {
  }

  void Engine::Initialize()
  {
    Instance = this;
    
    // Initialize the window.
    WindowManager::WindowData data = {};
    data.decorated_ = true;
    data.width_ = 1280;
    data.height_ = 720;
    data.title_ = u8"Barrage Engine";
    windowManager_.Initialize(data);
    
    // Initialize the graphics modules.
    gfxManager_.Initialize(windowManager_);
    gfxRenderer_.Initialize(gfxManager_);
    gfxFactory_.Initialize(gfxManager_);
    gfxRegistry_.Initialize(gfxFactory_);
    gfxDrawSystem_.Initialize(gfxManager_, gfxRenderer_, gfxRegistry_);

    inputManager_.Initialize(windowManager_.GetInternalHandle());
    framerateController_.Initialize(windowManager_.GetInternalHandle(), FramerateController::FpsCap::FPS_120, true);

    logger_.AddFileLogger("logs/trace.txt");
  }

  void Engine::Shutdown()
  {
    inputManager_.Shutdown();

    gfxDrawSystem_.Shutdown();
    gfxRegistry_.Shutdown();
    gfxFactory_.Shutdown();
    gfxRenderer_.Shutdown();
    gfxManager_.Shutdown();
    windowManager_.Shutdown();

    Instance = nullptr;
  }

  FramerateController& Engine::Frames()
  {
    return framerateController_;
  }

  GfxDraw2D& Engine::Drawing()
  {
    return gfxDrawSystem_;
  }

  GfxRegistry2D& Engine::GfxRegistry()
  {
    return gfxRegistry_;
  }

  InputManager& Engine::Input()
  {
    return inputManager_;
  }

  SpaceManager& Engine::Spaces()
  {
    return spaceManager_;
  }

  WindowManager& Engine::Windowing()
  {
    return windowManager_;
  }
}