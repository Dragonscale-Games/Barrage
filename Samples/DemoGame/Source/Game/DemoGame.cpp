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
#include "Source/GameStates/GS_DemoGame.hpp"

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

    engine_.GSM().SetGameState(GS_DemoGame());
  }

  void Game::Update()
  {
    engine_.Input().Update();

    Barrage::TestRenderer::Instance().StartFrame();

    if (engine_.GSM().GameStateIsRunning())
      engine_.GSM().Update();
    else
      isRunning_ = false;

    Barrage::TestRenderer::Instance().EndFrame();

    if (Barrage::TestRenderer::Instance().WindowClosed())
      isRunning_ = false;
  }

  void Game::Shutdown()
  {
    engine_.Instance->Shutdown();

    Barrage::Engine::Instance = nullptr;
  }
}