/* ======================================================================== */
/*!
 * \file            Game.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Standard game loop for Barrage Engine.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "Game.hpp"

#include <iostream>

namespace Barrage
{
  Game::Game() :
    isRunning_(false)
  {
  }

  void Game::Run()
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

  void Game::Initialize()
  {
    Engine::Get().Initialize();
  }

  void Game::Update()
  {
    Engine& engine = Engine::Get();
    
    engine.Frames().StartFrame();
    
    engine.Input().Reset();
    engine.Window().PollEvents();

    // Update game
    if (engine.Input().KeyTriggered(GLFW_KEY_P))
    {
      std::cout << "P triggered." << std::endl;
    }

    if (engine.Input().KeyIsDown(GLFW_KEY_P))
    {
      std::cout << "P down." << std::endl;
    }

    if (engine.Input().KeyReleased(GLFW_KEY_P))
    {
      std::cout << "P released." << std::endl;
    }

    engine.Graphics().GetFramebuffer().BindFramebuffer();
    engine.Graphics().ClearBackground();
    // Draw
    engine.Graphics().GetFramebuffer().UnbindFramebuffer();
    engine.Graphics().DrawFsq();
    engine.Window().SwapBuffers();

    if (engine.Window().IsClosed())
    {
      isRunning_ = false;
    }

    engine.Frames().EndFrame(!engine.Window().IsFocused());
  }

  void Game::Shutdown()
  {
    Engine::Get().Shutdown();
  }
}