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

#include "stdafx.h"
#include "Game.hpp"
#include "Registration/Registrar.hpp"

#include <string>
#include <rttr/registration.h>

#include <memory>

using namespace Barrage;

RTTR_REGISTRATION
{
  Registrar::Reflection();
}

int main()
{
  std::unique_ptr<Game> game = std::make_unique<Game>();

  game->Run();

  return 0;
}