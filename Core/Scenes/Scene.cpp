/* ======================================================================== */
/*!
 * \file            Scene.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A scene is a list of pools and game objects to spawn in a space.
 */
/* ======================================================================== */

#include "Scene.hpp"

namespace Barrage
{
  Scene::Scene() :
    startingPools_(),
    rngSeed_(0)
  {
  }

  void Scene::AddStartingPool(const PoolInfo& startingPool)
  {
    startingPools_.push_back(startingPool);
  }
}