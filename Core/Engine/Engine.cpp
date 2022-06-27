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
    TestRenderer::Instance().Initialize();

    inputManager_.Initialize(TestRenderer::Instance().GetWindowHandle());

    objectManager_.Initialize();
  }

  void Engine::Shutdown()
  {
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
}