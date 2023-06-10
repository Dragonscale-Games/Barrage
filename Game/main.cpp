/* ======================================================================== */
/*!
 * \file            main.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Entry point for the demo game.
 */
 /* ======================================================================== */

#include "Game.hpp"

int main()
{
  Barrage::Game* game = new Barrage::Game();

  game->Run();

  delete game;

  return 0;
}