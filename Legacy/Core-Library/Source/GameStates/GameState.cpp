/* ======================================================================== */
/*!
 * \file            GameState.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base game state class. To create a custom game state:
     1. Create a class that's derived from GameState.
     2. Create three static member functions:
        static void Enter();
        static void Update();
        static void Exit();
     3. Create a default constructor for the custom game state class with no 
        parameters, and set the class's enter_, update_, and exit_ fields to 
        the corresponding static functions.
 */
/* ======================================================================== */

#include "stdafx.h"
#include "GameState.hpp"

namespace Barrage
{
  GameState::GameState(GSFunc enter, GSFunc update, GSFunc exit) :
    enter_(enter), update_(update), exit_(exit)
  {
  }

  bool GameState::operator==(const GameState& rhs) const
  {
    return (rhs.enter_ == enter_) && (rhs.update_ == update_) && (rhs.exit_ == exit_);
  }

  bool GameState::operator!=(const GameState& rhs) const
  {
    return !(*this == rhs);
  }
}