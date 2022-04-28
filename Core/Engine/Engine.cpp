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
#include "TempRenderer/TestRenderer.hpp"
#include "GameStates/GameStateManager.hpp"
#include "Input/InputManager.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Barrage
{
  Engine* Engine::Instance = nullptr;

  Engine::Engine() :
    gsManager_(),
    inputManager_(),
    objectManager_()
  {
  }

  void Engine::Initialize()
  {
    TestRenderer::Instance().Initialize();

    inputManager_.Initialize(TestRenderer::Instance().GetWindowHandle());
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
}