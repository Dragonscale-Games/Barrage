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

#include <cstdio>
#include "rapidjson/filereadstream.h"
#include <iostream>

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
    engine_.Initialize();

    Entry entry = Entry::LoadFromFile("./Assets/entry.json");
    engine_.SetUpGame(entry);
    
    std::vector<std::string> spaceNames = engine_.Spaces().GetSpaceNames();

    for (auto it = spaceNames.begin(); it != spaceNames.end(); ++it)
    {
      std::cout << "Found space: " << *it << std::endl;
    }

    if (spaceNames.empty())
    {
      std::cout << "No spaces found." << std::endl;
    }
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

    engine_.Graphics().StartFrame();
    engine_.Graphics().StartFramebufferRendering();
    engine_.Spaces().Draw();
    engine_.Graphics().EndFramebufferRendering();
    engine_.Graphics().DrawFSQ();
    engine_.Graphics().EndFrame();

    if (engine_.Graphics().WindowClosed())
    {
      isRunning_ = false;
    }

    engine_.Frames().EndFrame();
  }

  void Game::Shutdown()
  {
    engine_.Shutdown();
  }
}