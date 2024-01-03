/* ======================================================================== */
/*!
 * \file            Pool.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   An object pool is a block of memory that can hold a prespecified number
   of objects with a specific combination of components.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "Pool.hpp"
#include "Objects/Components/ComponentFactory.hpp"

namespace Barrage
{
  Pool::Pool(const PoolArchetype& archetype) :
    components_(archetype.components_),
    componentArrays_(),
    tags_(archetype.tags_),
    spawnArchetypes_(archetype.spawnArchetypes_),
    numActiveObjects_(0),
    numQueuedObjects_(0),
    capacity_(archetype.capacity_),
    name_(archetype.name_)
  {
    for (const auto& componentArrayName : archetype.componentArrayNames_)
    {
      ComponentArrayPtr componentArray = ComponentFactory::AllocateComponentArray(componentArrayName, capacity_);

      // TODO: Log/throw something if these conditions aren't met
      if (componentArray && componentArrays_.count(componentArrayName) == 0)
      {
        componentArrays_.emplace(componentArrayName, componentArray);
      }
    }

    for (const auto& pair : archetype.startingObjects_)
    {
      // TODO: Log/throw something if this condition isn't met
      if (GetAvailableSlots())
      {
        CreateObjectsUnsafe(pair.second, 1);
        numActiveObjects_++;
      }
    }
  }

  unsigned Pool::ActiveObjectCount() const
  {
    return numActiveObjects_;
  }

  void Pool::QueueSpawns(Space& space, Pool& sourcePool, SpawnType& spawnType)
  {
    spawnType.CalculateObjectsPerGroup();
    
    unsigned numObjects = spawnType.GetNumberOfObjectsToSpawn();
    unsigned availableSlots = GetAvailableSlots();
    ObjectArchetype& spawnArchetype = spawnArchetypes_.at(spawnType.spawnArchetypeName_);
    
    if (numObjects > availableSlots)
    {
      numObjects = availableSlots;
    }

    if (numObjects != 0)
    {
      CreateObjectsUnsafe(spawnArchetype, numObjects);
      numQueuedObjects_ += numObjects;
    }
    
    // apply value spawn rules
    // apply size spawn rules

    spawnType.ClearSpawns();
  }

  void Pool::SpawnObjects()
  {
    numActiveObjects_ += numQueuedObjects_;
    numQueuedObjects_ = 0;
  }

  bool Pool::HasComponent(const std::string& componentName)
  {
    return components_.count(componentName);
  }

  bool Pool::HasComponentArray(const std::string& componentArrayName)
  {
    return componentArrays_.count(componentArrayName);
  }

  bool Pool::HasTag(const std::string& tag) const
  {
    return tags_.count(tag);
  }

  unsigned Pool::GetAvailableSlots() const
  {
    return capacity_ - GetSpawnIndex();
  }

  unsigned Pool::GetSpawnIndex() const
  {
    return numActiveObjects_ + numQueuedObjects_;
  }

  void Pool::CreateObjectsUnsafe(const ObjectArchetype& archetype, unsigned numObjects)
  {
    unsigned startIndex = GetSpawnIndex();
    
    for (auto it = componentArrays_.begin(); it != componentArrays_.end(); ++it)
    {
      ComponentArrayPtr destination_array = it->second;
      const ComponentArrayPtr source_component = archetype.componentArrays_.at(it->first);

      for (unsigned i = 0; i < numObjects; ++i)
      {
        destination_array->CopyToThis(*source_component, 0, startIndex + i);
      }
    }
  }
}