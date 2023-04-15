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

namespace Barrage
{
  PoolManager::PoolManager(ComponentAllocator& componentAllocator, Space& space) :
    pools_(),
    componentAllocator_(componentAllocator),
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
    if (pools_.find(archetype.name_) == pools_.end())
    {
      Pool* new_pool = CreatePoolInternal(archetype);
      pools_[archetype.name_] = new_pool;

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
    Pool* new_pool = new Pool(archetype.capacity_, space_);

    // add tags
    for (const std::string_view& tag : archetype.tags_)
    {
      new_pool->tags_.insert(tag);
    }

    // allocate component arrays
    for (const std::string_view& component_array_name : archetype.componentArrayNames_)
    {
      ComponentArray* component_array = componentAllocator_.AllocateComponentArray(component_array_name, archetype.capacity_);

      if (component_array)
      {
        new_pool->componentArrays_[component_array_name] = component_array;
      }
    }

    // allocate and initialize shared components
    for (auto it = archetype.sharedComponents_.begin(); it != archetype.sharedComponents_.end(); ++it)
    {
      SharedComponent* shared_component = componentAllocator_.AllocateSharedComponent(it->first, it->second);

      if (shared_component)
      {
        new_pool->sharedComponents_[it->first] = shared_component;
      }
    }
    
    // copy over spawn archetypes
    for (auto it = archetype.spawnArchetypes_.begin(); it != archetype.spawnArchetypes_.end(); ++it)
    {
      const ObjectArchetype& spawnArchetype = *it;

      new_pool->spawnArchetypes_.insert(std::make_pair(spawnArchetype.name_, spawnArchetype));
    }



    return new_pool;
  }
}