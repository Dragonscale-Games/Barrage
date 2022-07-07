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
    gsManager_(),
    inputManager_(),
    objectManager_(),
    rng_()
  {
  }

  void Engine::Initialize()
  {
    //TestRenderer::Instance().Initialize();

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

    //inputManager_.Initialize(TestRenderer::Instance().GetWindowHandle());
    inputManager_.Initialize(windowManager_.GetInternalHandle());

    objectManager_.Initialize();
  }

  void Engine::Shutdown()
  {
    gfxDrawSystem_.Shutdown();
    gfxRegistry_.Shutdown();
    gfxFactory_.Shutdown();
    gfxRenderer_.Shutdown();
    gfxManager_.Shutdown();
    windowManager_.Shutdown();

    inputManager_.Shutdown();

    TestRenderer::Instance().Shutdown();
  }

  GameStateManager& Engine::GSM()
  {
    return gsManager_;
  }

  InputManager& Engine::Input()
  {
    return inputManager_;
  }

  ObjectManager& Engine::Objects()
  {
    return objectManager_;
  }

  Random& Engine::RNG()
  {
    return rng_;
  }

  WindowManager& Engine::Windowing()
  {
    return windowManager_;
  }

  GfxDraw2D& Engine::Drawing()
  {
    return gfxDrawSystem_;
  }

  GfxRegistry2D& Engine::Registry()
  {
    return gfxRegistry_;
  }
}