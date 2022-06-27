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

namespace Barrage
{
  PoolManager::PoolManager(ComponentAllocator& componentAllocator) :
    pools_(),
    componentAllocator_(componentAllocator)
  {
  }

  PoolManager::~PoolManager()
  {
    for (auto it = pools_.begin(); it != pools_.end(); ++it)
    {
      delete it->second;
    }
  }

  Pool* PoolManager::CreatePool(const std::string& name, const PoolArchetype& archetype, unsigned capacity)
  {
    if (pools_.find(name) == pools_.end())
    {
      Pool* new_pool = CreatePoolInternal(archetype, capacity);
      pools_[name] = new_pool;

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

  PoolList PoolManager::GetPoolNames()
  {
    PoolList pool_list;

    for (auto it = pools_.begin(); it != pools_.end(); ++it)
    {
      pool_list.push_back(it->first);
    }

    return pool_list;
  }

  Pool* PoolManager::CreatePoolInternal(const PoolArchetype& archetype, unsigned capacity)
  {
    Pool* new_pool = new Pool(capacity);

    // add tags
    for (const std::string& tag : archetype.tags_)
    {
      new_pool->tags_.insert(tag);
    }

    // allocate component arrays
    for (const std::string& component_array_name : archetype.componentArrayNames_)
    {
      ComponentArray* component_array = componentAllocator_.AllocateComponentArray(component_array_name, capacity);

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

    return new_pool;
  }
}