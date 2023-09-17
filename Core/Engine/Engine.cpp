/* ======================================================================== */
/*!
 * \file            Engine.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   In charge of setting up engine modules (renderer, input, etc).
 */
 /* ======================================================================== */

#include "Engine.hpp"

#include <iostream>

namespace Barrage
{
  Engine& Engine::Get()
  {
    static Engine instance; // not constructed until first time Get() is called
    return instance;
  }

  void Engine::Initialize()
  {
    std::cout << "Engine initialized." << std::endl;
  }

  void Engine::Shutdown()
  {
    std::cout << "Engine shut down." << std::endl;
  }
}