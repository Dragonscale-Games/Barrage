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

#include "Rendering/GfxManager2D.hpp"
#include "Rendering/GfxRenderer2D.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Barrage
{
  Engine* Engine::Instance = nullptr;

  Engine::Engine() :
    gsManager_(nullptr),
    inputManager_(nullptr),
    objectManager_(nullptr),
    gfxManager_(nullptr),
    gfxRenderer_(nullptr),
    windowManager_(nullptr)
  {
  }

  void Engine::Initialize()
  {
    TestRenderer::Instance().Initialize();

    inputManager_ = new InputManager;
    inputManager_->Initialize(TestRenderer::Instance().GetWindowHandle());

    objectManager_ = new ObjectManager;

    gsManager_ = new GameStateManager;

    gfxManager_ = new GfxManager2D;
    gfxRenderer_ = new GfxRenderer2D;
    gfxRenderer_->Initialize(*gfxManager_);
    // TODO: Eventually initialize the system with the new window
  }

  void Engine::Shutdown()
  {
    gfxRenderer_->Shutdown();
    delete gfxRenderer_;

    gfxManager_->CleanAllResources();
    delete gfxManager_;

    gsManager_->Shutdown();
    delete gsManager_;
    gsManager_ = nullptr;

    delete objectManager_;

    inputManager_->Shutdown();
    delete inputManager_;
    inputManager_ = nullptr;

    TestRenderer::Instance().Shutdown();
  }

  GameStateManager& Engine::GSM()
  {
    return *(Instance->gsManager_);
  }

  InputManager& Engine::Input()
  {
    return *(Instance->inputManager_);
  }

  ObjectManager& Engine::Objects()
  {
    return *(Instance->objectManager_);
  }

  GfxManager2D& Engine::GfxManager()
  {
    return *(Instance->gfxManager_);
  }

  GfxRenderer2D& Engine::GfxRenderer()
  {
    return *(Instance->gfxRenderer_);
  }
}