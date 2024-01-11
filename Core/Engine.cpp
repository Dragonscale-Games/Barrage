/* ======================================================================== */
/*!
 * \file            Engine.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   In charge of setting up engine modules (renderer, input, etc).
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "Engine.hpp"
#include "Registration/Registrar.hpp"

namespace Barrage
{
  Engine* Engine::instance_ = nullptr;
  
  Engine::Engine() :
    audioManager_(),
    framerateController_(),
    inputManager_(),
    renderer_(),
    sceneManager_(),
    spaceManager_(),
    windowManager_()
  {
  }
  
  Engine& Engine::Get()
  {
    return *instance_;
  }

  void Engine::Initialize()
  {
    instance_ = this;
    Registrar::Registration();
    windowManager_.Initialize();
    inputManager_.Initialize(windowManager_.GetWindowHandle());
    renderer_.Initialize(WindowManager::DEFAULT_WIDTH, WindowManager::DEFAULT_HEIGHT);
    audioManager_.Initialize();

    framerateController_.Initialize(FramerateController::FpsCap::FPS_120, true);
    
    glfwSetFramebufferSizeCallback(windowManager_.GetWindowHandle(), FramebufferSizeCallback);
  }

  void Engine::Shutdown()
  {
    audioManager_.Shutdown();
    renderer_.Shutdown();
    inputManager_.Shutdown();
    windowManager_.Shutdown();

    instance_ = nullptr;
  }
  
  AudioManager& Engine::Audio()
  {
    return audioManager_;
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

  WindowManager& Engine::Window()
  {
    return windowManager_;
  }

  void Engine::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
  {
    UNREFERENCED(window);

    Engine::Get().Graphics().SetViewport(width, height);
    Engine::Get().Graphics().GetFramebuffer().Resize(width, height);
  }
}