/* ======================================================================== */
/*!
 * \file            Space.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A space is a collection of scenes and game objects. Each space represents
   a unique simulation.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "Space.hpp"

namespace Barrage
{
  Space::Space() :
    objectManager_(),
    sceneManager_(objectManager_)
  {
  }

  void Space::SetScene(const std::string name)
  {
    sceneManager_.SetScene(name);
  }
}