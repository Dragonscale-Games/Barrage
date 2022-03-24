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

    // allocate object component arrays
    for (const std::string& component : archetype.objectComponents_)
    {
      ObjectComponent* object_component_array = componentAllocator_.AllocateObjectComponentArray(component, capacity);

      if (object_component_array)
      {
        new_pool->objectComponents_[component] = object_component_array;
      }
    }

    // allocate and initialize pool components
    for (auto it = archetype.poolComponents_.begin(); it != archetype.poolComponents_.end(); ++it)
    {
      PoolComponent* pool_component = componentAllocator_.AllocatePoolComponent(it->first, it->second);

      if (pool_component)
      {
        new_pool->poolComponents_[it->first] = pool_component;
      }
    }

    return new_pool;
  }
}