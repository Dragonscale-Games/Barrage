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
    startingPools_()
  {
  }

  bool Scene::HasPool(const std::string& poolName)
  {
    return startingPools_.count(poolName);
  }

  void Scene::AddStartingPool(const PoolInfo& startingPool)
  {
    if (HasPool(startingPool.poolName_))
    {
      return;
    }

    startingPools_.insert(std::make_pair(startingPool.poolName_, startingPool));
  }

  bool Scene::HasObject(const std::string& poolName, const std::string& objectName)
  {
    if (!HasPool(poolName))
    {
      return false;
    }

    PoolInfo& pool = startingPools_.at(poolName);

    return pool.objects_.count(objectName);
  }

  void Scene::AddObject(const std::string& poolName, const std::string& objectName)
  {
    if (!HasPool(poolName))
    {
      return;
    }

    startingPools_.at(poolName).objects_.insert(objectName);
  }
}