/* ======================================================================== */
/*!
 * \file            PoolManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 

 */
/* ======================================================================== */

#include "stdafx.h"
#include "PoolManager.hpp"
#include "Spaces/Space.hpp"
#include "Objects/Components/ComponentAllocator.hpp"

namespace Barrage
{
  PoolManager::PoolManager(Space& space) :
    pools_(),
    space_(space)
  {
  }

  PoolManager::~PoolManager()
  {
    for (auto it = pools_.begin(); it != pools_.end(); ++it)
    {
      delete it->second;
    }
  }

  Pool* PoolManager::CreatePool(const PoolArchetype& archetype)
  {
    if (archetype.GetCapacity() == 0)
    {
      return nullptr;
    }
    
    const std::string& archetypeName = archetype.GetName();
    
    if (pools_.find(archetypeName) == pools_.end())
    {
      Pool* new_pool = CreatePoolInternal(archetype);
      pools_[archetypeName] = new_pool;

      return new_pool;
    }
    else
    {
      return nullptr;
    }
  }

  Pool* PoolManager::GetPool(const std::string& name) const
  {
    if (pools_.find(name) == pools_.end())
    {
      return nullptr;
    }
    else
    {
      return pools_.at(name);
    }
  }

  void PoolManager::DeletePool(const std::string& name)
  {
    if (pools_.find(name) != pools_.end())
    {
      delete pools_.at(name);
      pools_.erase(name);
    }
  }

  std::vector<std::string> PoolManager::GetPoolNames()
  {
    std::vector<std::string> pool_list;

    for (auto it = pools_.begin(); it != pools_.end(); ++it)
    {
      pool_list.push_back(it->first);
    }

    return pool_list;
  }

  Pool* PoolManager::CreatePoolInternal(const PoolArchetype& archetype)
  {
    Pool* new_pool = new Pool(archetype.GetName(), archetype.GetCapacity(), space_);

    // add tags
    const std::vector<std::string_view> tags = archetype.GetTags();
    for (const std::string_view& tag : tags)
    {
      new_pool->AddTag(tag);
    }

    // allocate and initialize components
    const ComponentUmap& components = archetype.GetComponents();
    for (auto it = components.begin(); it != components.end(); ++it)
    {
      new_pool->AddComponent(it->first, it->second);
    }

    // allocate component arrays
    const std::vector<std::string_view> componentArrayNames = archetype.GetComponentArrayNames();
    for (const std::string_view& component_array_name : componentArrayNames)
    {
      new_pool->AddComponentArray(component_array_name);
    }

    // copy over spawn archetypes
    const std::vector<ObjectArchetype*>& spawnArchetypes = archetype.GetSpawnArchetypes();
    for (auto it = spawnArchetypes.begin(); it != spawnArchetypes.end(); ++it)
    {
      new_pool->AddSpawnArchetype(**it);
    }

    // create starting objects
    const std::vector<ObjectArchetype*>& startingObjects = archetype.GetStartingObjects();
    for (auto it = startingObjects.begin(); it != startingObjects.end(); ++it)
    {
      new_pool->CreateObject(**it);
    }

    return new_pool;
  }
}