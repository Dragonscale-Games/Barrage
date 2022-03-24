/* ======================================================================== */
/*!
 * \file            SceneManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 

 */
/* ======================================================================== */

#include "stdafx.h"
#include "SceneManager.hpp"

namespace Barrage
{
  SceneManager::SceneManager(ObjectManager& objectManager) :
    scenes_(),
    objectManager_(objectManager)
  {
  }

  SceneManager::~SceneManager()
  {
    for (auto it = scenes_.begin(); it != scenes_.end(); ++it)
    {
      delete it->second;
    }
  }

  void SceneManager::SetScene(const std::string& sceneName) const
  { 
    if (scenes_.find(sceneName) == scenes_.end())
      return;

    objectManager_.DeleteAllPools();

    Scene* scene = scenes_.at(sceneName);
    const std::vector<Scene::PoolInfo>& starting_pools = scene->GetStartingPools();

    for (auto it = starting_pools.begin(); it != starting_pools.end(); ++it)
    {
      const Scene::PoolInfo& pool_info = *it;

      const std::string& pool_name = pool_info.GetPoolName();
      const std::string& pool_archetype_name = pool_info.GetPoolArchetypeName();
      unsigned pool_capacity = pool_info.GetPoolCapacity();

      objectManager_.CreatePool(pool_name, pool_archetype_name, pool_capacity);
      
      const ObjectList& object_list = pool_info.GetObjectList();

      for (auto jt = object_list.begin(); jt != object_list.end(); ++jt)
      {
        objectManager_.CreateObject(pool_name, *jt);
      }
    }
  }

  void SceneManager::LoadScene(const std::string& name)
  {

  }

  void SceneManager::SaveScene(const std::string& name) const
  {

  }
}