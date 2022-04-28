/* ======================================================================== */
/*!
 * \file            GSCruse.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <description>

 */
/* ======================================================================== */

#include "GSCruse.hpp"
#include "GameStates/GSEntry.hpp"
#include "GameStates/TestGameStates/Cruse/GSBulletTest.hpp"
#include "GameStates/TestGameStates/Cruse/GSMetaballs.hpp"

#include <Engine/Engine.hpp>

namespace Barrage
{
  GSCruse::GSCruse() : GameState(Enter, Update, Exit)
  {
  }

  void GSCruse::Enter()
  {
    
  }

  void GSCruse::Update()
  {
    if (Engine::Input().KeyTriggered(KEY_BACKSPACE))
    {
      Engine::GSM().SetGameState(GSEntry());
    }
    if (Engine::Input().KeyTriggered(KEY_1))
    {
      Engine::GSM().SetGameState(GSBulletTest());
    }
    if (Engine::Input().KeyTriggered(KEY_2))
    {
      Engine::GSM().SetGameState(GSBulletTest());
    }
  }

  void GSCruse::Exit()
  {
    
  }
}