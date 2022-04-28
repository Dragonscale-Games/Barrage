/* ======================================================================== */
/*!
 * \file            GSEntry.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Initial game state for the engine.

 */
/* ======================================================================== */

#include "GSEntry.hpp"
#include "TestGameStates/GSBaldeon.hpp"
#include "TestGameStates/GSCruse.hpp"
#include "TestGameStates/GSWong.hpp"

#include "GameStates/TestGameStates/Cruse/GSBulletTest.hpp"
#include "GameStates/TestGameStates/Cruse/GSMetaballs.hpp"

#include <Engine/Engine.hpp>
#include <TempRenderer/TestRenderer.hpp>

namespace Barrage
{
  int GSEntry::cursorPosition_ = 1;
  
  GSEntry::GSEntry() : GameState(Enter, Update, Exit)
  {
  }

  void GSEntry::Enter()
  {
    
  }

  void GSEntry::Update()
  {
    if (Engine::Input().KeyTriggered(KEY_RIGHT))
    {
      cursorPosition_++;

      if (cursorPosition_ == 3)
        cursorPosition_ = 0;
    }

    if (Engine::Input().KeyTriggered(KEY_LEFT))
    {
      cursorPosition_--;

      if (cursorPosition_ == -1)
        cursorPosition_ = 2;
    }
    
    if (Engine::Input().KeyTriggered(KEY_ENTER) || 
        Engine::Input().KeyTriggered(KEY_ENTER_NUMPAD) || 
        Engine::Input().KeyTriggered(KEY_SPACE) || 
        Engine::Input().KeyTriggered(KEY_Z))
    {
      switch (cursorPosition_)
      {
        case 0:
          Engine::GSM().SetGameState(GSBaldeon());
          break;

        case 1:
          Engine::GSM().SetGameState(GSWong());
          break;

        case 2:
          Engine::GSM().SetGameState(GSBulletTest());
          break;
      }
    }

    if (Engine::Input().KeyTriggered(KEY_ESCAPE))
    {
      Engine::GSM().QuitGameState();
    }

    glm::vec2 cursor_coordinates;

    switch (cursorPosition_)
    {
      case 0:
        cursor_coordinates = glm::vec2(-480.0f, -260.0f);
        break;

      case 1:
        cursor_coordinates = glm::vec2(60.0f, -260.0f);
        break;

      case 2:
        cursor_coordinates = glm::vec2(540.0f, -260.0f);
        break;
    }

    TestRenderer::Instance().Draw(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(1280.0f, 720.0f), "BarrageSplash");
    TestRenderer::Instance().Draw(cursor_coordinates, 0.0f, glm::vec2(100.0f, 100.0f), "Cursor");
  }

  void GSEntry::Exit()
  {
    
  }
}