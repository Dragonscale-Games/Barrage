/* ======================================================================== */
/*!
 * \file            DemoGame.hpp
 * \par             Demo Game
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A simple game environment using Barrage Engine.
 */
 /* ======================================================================== */

#include "DemoGame.hpp"
#include "../Initialization/DemoInitialization.hpp"

namespace Demo
{
  Game::Game() :
    engine_(),
    isRunning_()
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
    Barrage::Engine::Instance = &engine_;

    engine_.Initialize();

    Barrage::Space* demo_space = CreateDemoSpace();

    engine_.Spaces().AddSpace("Demo Space", demo_space);
  }

  void Game::Update()
  {
    engine_.Frames().StartFrame();
    
    engine_.Input().Update();

    unsigned num_ticks = engine_.Frames().ConsumeTicks();
    for (unsigned i = 0; i < num_ticks; ++i)
    {
      engine_.Spaces().Update();
    }

    engine_.Render().StartFrame();
    engine_.Spaces().Draw();
    engine_.Render().EndFrame();

    if (engine_.Render().WindowClosed())
      isRunning_ = false;

    engine_.Frames().EndFrame();
  }

  void Game::Shutdown()
  {
    engine_.Shutdown();

    Barrage::Engine::Instance = nullptr;
  }
}