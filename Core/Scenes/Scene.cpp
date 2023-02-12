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
    for (auto it = startingPools_.begin(); it != startingPools_.end(); ++it)
    {
      if (it->poolName_ == poolName)
      {
        return true;
      }
    }
    
    return false;
  }

  void Scene::AddStartingPool(const PoolInfo& startingPool)
  {
    if (HasPool(startingPool.poolName_))
    {
      return;
    }

    startingPools_.push_back(startingPool);
  }

  void Scene::RemovePool(const std::string& poolName)
  {
    for (auto it = startingPools_.begin(); it != startingPools_.end(); ++it)
    {
      if (it->poolName_ == poolName)
      {
        startingPools_.erase(it);
        return;
      }
    }
  }

  bool Scene::HasObject(const std::string& poolName, const std::string& objectName)
  {
    for (auto it = startingPools_.begin(); it != startingPools_.end(); ++it)
    {
      PoolInfo& pool = *it;
      
      if (pool.poolName_ == poolName)
      {
        for (auto jt = pool.objects_.begin(); jt != pool.objects_.end(); ++jt)
        {
          if (*jt == objectName)
          {
            return true;
          }
        }
      }
    }

    return false;
  }

  void Scene::AddObject(const std::string& poolName, const std::string& objectName)
  {    
    if (HasObject(poolName, objectName))
    {
      return;
    }
    
    for (auto it = startingPools_.begin(); it != startingPools_.end(); ++it)
    {
      if (it->poolName_ == poolName)
      {
        it->objects_.push_back(objectName);
      }
    }
  }

  void Scene::RemoveObject(const std::string& poolName, const std::string& objectName)
  {
    for (auto it = startingPools_.begin(); it != startingPools_.end(); ++it)
    {
      PoolInfo& pool = *it;

      if (pool.poolName_ == poolName)
      {
        for (auto jt = pool.objects_.begin(); jt != pool.objects_.end(); ++jt)
        {
          if (*jt == objectName)
          {
            pool.objects_.erase(jt);
            return;
          }
        }
      }
    }
  }
}