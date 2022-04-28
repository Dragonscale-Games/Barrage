/* ======================================================================== */
/*!
 * \file            Game.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 

 */
/* ======================================================================== */

#include "stdafx.h"
#include "Game.hpp"

#include <GameStates/GSEntry.hpp>
#include <TempRenderer/TestRenderer.hpp>

namespace Barrage
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

    engine_.GSM().SetGameState(Barrage::GSEntry());
  }

  void Game::Update()
  {
    engine_.Input().Update();

    TestRenderer::Instance().StartFrame();

    if (engine_.GSM().GameStateIsRunning())
      engine_.GSM().Update();
    else
      isRunning_ = false;

    TestRenderer::Instance().EndFrame();

    if (TestRenderer::Instance().WindowClosed())
      isRunning_ = false;
  }

  void Game::Shutdown()
  {
    engine_.Instance->Shutdown();

    Barrage::Engine::Instance = nullptr;
  }
}