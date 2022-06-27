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

#include "Game/DemoGame.hpp"

int main()
{
  Demo::Game* game = new Demo::Game();

  game->Run();

  delete game;

  return 0;
}