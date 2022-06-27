/* ======================================================================== */
/*!
 * \file            GS_DemoGame.cpp
 * \par             Demo Game
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Demo game state.
 */
/* ======================================================================== */

#include "stdafx.h"
#include "GS_DemoGame.hpp"

#include <Engine/Engine.hpp>

#include <iostream>

namespace Demo
{
  bool GS_DemoGame::isPaused_ = false;
  
  GS_DemoGame::GS_DemoGame() : Barrage::GameState(Enter, Update, Exit)
  {
  }

  void GS_DemoGame::Enter()
  {
    const unsigned MAX_BULLETS = 100000;

    isPaused_ = false;

    Barrage::Engine::Instance->Objects().CreatePool("Player Pool", "Player Pool Archetype");
    Barrage::Engine::Instance->Objects().CreateObject("Player Pool", "Player Object Archetype");

    Barrage::Engine::Instance->Objects().CreatePool("Spawner Pool", "Spawner Pool Archetype");
    Barrage::Engine::Instance->Objects().CreateObject("Spawner Pool", "Spawner Object Archetype");

    Barrage::Engine::Instance->Objects().CreatePool("Bullet Pool", "Bullet Pool Archetype", MAX_BULLETS);
  }

  void GS_DemoGame::Update()
  {
    if (Barrage::Engine::Instance->Input().KeyTriggered(Barrage::KEY_ESCAPE))
    {
      isPaused_ = !isPaused_;
    }
    
    if (!isPaused_)
    {
      Barrage::Engine::Instance->Objects().Update();
    }
    
    Barrage::Engine::Instance->Objects().Draw();
  }

  void GS_DemoGame::Exit()
  {
    Barrage::Engine::Instance->Objects().DeleteAllPools();
  }
}