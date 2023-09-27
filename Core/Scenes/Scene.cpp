/* ======================================================================== */
/*!
 * \file            Scene.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A scene is a list of pools (and their objects) to spawn in a space.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "Scene.hpp"

namespace Barrage
{
  Scene::Scene(const std::string& name) :
    name_(name),
    poolArchetypes_()
  {
  }
}