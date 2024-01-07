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
#include "Objects/Spawning/SpawnType.hpp"

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
      GenericComponentArray componentArray = ComponentFactory::AllocateComponentArray(componentArrayName, capacity_);

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

  unsigned Pool::GetCapacity() const
  {
    return capacity_;
  }

  void Pool::QueueSpawns(Space& space, Pool& sourcePool, SpawnType& spawnType)
  {
    spawnType.FinalizeGroupInfo();
    
    unsigned numObjects = spawnType.CalculateSpawnSize(GetAvailableSlots());

    if (numObjects != 0)
    {
      ObjectArchetype& spawnArchetype = spawnArchetypes_.at(spawnType.spawnArchetype_);
      CreateObjectsUnsafe(spawnArchetype, numObjects);

      ApplyValueSpawnRules(space, sourcePool, spawnType);
      ApplySizeSpawnRules(space, sourcePool, spawnType);

      numQueuedObjects_ += numObjects;

      spawnType.ClearSpawns();
    }
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
      GenericComponentArray& destination_array = it->second;
      const GenericComponentArray& source_component = archetype.componentArrays_.at(it->first);

      for (unsigned i = 0; i < numObjects; ++i)
      {
        destination_array->CopyToThis(*source_component, 0, startIndex + i);
      }
    }
  }

  void Pool::ApplyValueSpawnRules(Space& space, Pool& sourcePool, SpawnType& spawnType)
  {
    unsigned startIndex = GetSpawnIndex();
    
    for (auto it = spawnType.spawnLayers_.begin(); it != spawnType.spawnLayers_.end(); ++it)
    {
      SpawnLayer& spawnLayer = *it;

      spawnLayer.valueRules_.ApplyRules(sourcePool, *this, space, startIndex, spawnType.sourceIndices_, spawnLayer.groupInfoArray_);
    }
  }

  void Pool::ApplySizeSpawnRules(Space& space, Pool& sourcePool, SpawnType& spawnType)
  {
    unsigned startIndex = GetSpawnIndex();

    for (auto it = spawnType.spawnLayers_.begin(); it != spawnType.spawnLayers_.end(); ++it)
    {
      SpawnLayer& spawnLayer = *it;

      spawnLayer.sizeRules_.ApplyRules(sourcePool, *this, space, startIndex, spawnType.sourceIndices_, spawnLayer.groupInfoArray_);
    }
  }
}