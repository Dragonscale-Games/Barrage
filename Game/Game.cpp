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

namespace Barrage
{
  Game::Game() :
    engine_(),
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
    engine_.Initialize();
    engine_.Window().SetFullScreen();
    engine_.Frames().SetVsync(false);

    Entry entry = Entry::LoadFromFile("./Assets/entry.json");
    engine_.SetUpGame(entry);
  }

  void Game::Update()
  {
    engine_.Frames().StartFrame();
    
    engine_.Input().Reset();
    engine_.Window().PollEvents();

    if (engine_.Input().KeyTriggered(GLFW_KEY_ESCAPE))
    {
      engine_.Window().SetWindowed();
    }

    unsigned numTicks = engine_.Frames().ConsumeTicks();
    for (unsigned i = 0; i < numTicks; ++i)
    {
      engine_.Spaces().Update();
    }

    engine_.Graphics().GetFramebuffer().BindFramebuffer();
    engine_.Graphics().ClearBackground();
    engine_.Spaces().Draw();
    engine_.Graphics().GetFramebuffer().UnbindFramebuffer();
    engine_.Graphics().DrawFsq();
    engine_.Window().SwapBuffers();

    if (engine_.Window().IsClosed())
    {
      isRunning_ = false;
    }

    engine_.Frames().EndFrame(!engine_.Window().IsFocused());
  }

  void Game::Shutdown()
  {
    engine_.Shutdown();
  }
}