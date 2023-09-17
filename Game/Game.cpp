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

#include "Game.hpp"

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
    isRunning_ = false;
  }

  void Game::Shutdown()
  {
    Engine::Get().Shutdown();
  }
}