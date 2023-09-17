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

#include <memory>

using namespace Barrage;

int main()
{
  std::unique_ptr<Game> game = std::make_unique<Game>();

  game->Run();

  return 0;
}