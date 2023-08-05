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
#include <GLFW/glfw3.h>

namespace Barrage
{
  Engine* Engine::Instance = nullptr;

  void Engine::Initialize()
  {
    Instance = this;
    
    windowManager_.Initialize();
    renderer_.Initialize(WindowManager::DEFAULT_WIDTH, WindowManager::DEFAULT_HEIGHT);
    windowManager_.SetFramebufferSizeCallback(FramebufferSizeCallback);
    inputManager_.Initialize(windowManager_.GetWindowHandle());
    framerateController_.Initialize(windowManager_.GetWindowHandle(), FramerateController::FpsCap::FPS_120, true);
    audioManager_.Initialize();
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
    audioManager_.Shutdown();
    inputManager_.Shutdown();
    renderer_.Shutdown();
    windowManager_.Shutdown();

    Instance = nullptr;
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
    
    if (Instance)
    {
      Instance->Graphics().SetViewport(width, height);
      Instance->Graphics().GetFramebuffer().Resize(width, height);
    }
  }
}