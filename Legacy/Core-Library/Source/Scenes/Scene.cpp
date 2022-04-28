/* ======================================================================== */
/*!
 * \file            Scene.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 

 */
/* ======================================================================== */

#include "stdafx.h"
#include "Scene.hpp"

#include <stdexcept>

namespace Barrage
{
  Scene::PoolInfo::PoolInfo(const std::string& poolName, const std::string& archetypeName, unsigned capacity) :
    poolName_(poolName),
    archetypeName_(archetypeName),
    capacity_(capacity),
    objects_()
  {
  }
  
  void Scene::PoolInfo::AddObject(const std::string& archetypeName)
  {
    objects_.push_back(archetypeName);
  }

  const std::string& Scene::PoolInfo::GetPoolName() const
  {
    return poolName_;
  }

  const std::string& Scene::PoolInfo::GetPoolArchetypeName() const
  {
    return archetypeName_;
  }

  unsigned Scene::PoolInfo::GetPoolCapacity() const
  {
    return capacity_;
  }

  const ObjectList& Scene::PoolInfo::GetObjectList() const
  {
    return objects_;
  }

  Scene::Scene() :
    startingPools_()
  {
  }

  void Scene::AddStartingPool(const PoolInfo& startingPool)
  {
    startingPools_.push_back(startingPool);
  }

  const std::vector<Scene::PoolInfo>& Scene::GetStartingPools() const
  {
    return startingPools_;
  }
}