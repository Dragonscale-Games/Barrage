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
#include "Spaces/Space.hpp"

namespace Barrage
{
  Pool::Pool(const std::string& name, unsigned capacity, Space& space) :
    componentArrays_(),
    sharedComponents_(),
    spawnArchetypes_(),
    tags_(),
    numActiveObjects_(0),
    numQueuedObjects_(0),
    capacity_(capacity),
    name_(name),
    space_(space)
  {
  }

  Pool::~Pool()
  {
    // deallocate component arrays
    for (auto it = componentArrays_.begin(); it != componentArrays_.end(); ++it)
    {
      delete it->second;
    }

    // deallocate shared components
    for (auto it = sharedComponents_.begin(); it != sharedComponents_.end(); ++it)
    {
      delete it->second;
    }
  }

  void Pool::AddTag(const std::string_view& name)
  {
    tags_.insert(name);
  }

  void Pool::AddComponentArray(const std::string_view& name)
  {
    if (componentArrays_.count(name))
    {
      return;
    }

    ComponentArray* newArray = ComponentAllocator::AllocateComponentArray(name, capacity_);
    componentArrays_[name] = newArray;
  }

  void Pool::AddSharedComponent(const std::string_view& name, SharedComponent* initializer)
  {
    if (sharedComponents_.count(name))
    {
      return;
    }

    SharedComponent* newComponent = ComponentAllocator::AllocateSharedComponent(name, initializer);
    sharedComponents_[name] = newComponent;
  }

  void Pool::AddSpawnArchetype(const ObjectArchetype& spawnArchetype)
  {
    if (spawnArchetypes_.count(spawnArchetype.name_))
    {
      return;
    }

    spawnArchetypes_.insert(std::make_pair(spawnArchetype.name_, spawnArchetype));
  }

  void Pool::CreateObject(const ObjectArchetype& archetype)
  {
    unsigned availableSlots = GetAvailableSlots();
    
    if (availableSlots == 0)
    {
      return;
    }

    // if objects are queued for spawn, we need to shift them out of the memory the new active objects will occupy
    if (numQueuedObjects_)
    {
      ShiftQueuedObjects(1);
    }

    unsigned startIndex = numActiveObjects_;

    CreateObjectsInternal(archetype, startIndex, 1);

    numActiveObjects_++;
  }

  void Pool::QueueSpawns(SpawnInfo& spawnInfo)
  {
    unsigned numObjects = spawnInfo.sourceIndices_.size();
    unsigned availableSlots = GetAvailableSlots();

    if (numObjects > availableSlots)
    {
      numObjects = availableSlots;
    }

    unsigned startIndex = numActiveObjects_ + numQueuedObjects_;
    ObjectArchetype& archetype = spawnArchetypes_.at(spawnInfo.archetypeName_);

    CreateObjectsInternal(archetype, startIndex, numObjects);


    spawnInfo.sourceIndices_.clear();
    numQueuedObjects_ += numObjects;
  }

  bool Pool::HasTag(const std::string_view& tag) const
  {
    return tags_.count(tag);
  }

  bool Pool::HasComponentArray(const std::string_view& componentArrayName)
  {
    return componentArrays_.count(componentArrayName);
  }

  bool Pool::HasSharedComponent(const std::string_view& sharedComponentName)
  {
    return sharedComponents_.count(sharedComponentName);
  }

  unsigned Pool::GetAvailableSlots() const
  {
    return capacity_ - numActiveObjects_ - numQueuedObjects_;
  }

  unsigned Pool::GetActiveObjectCount() const
  {
    return numActiveObjects_;
  }

  unsigned Pool::GetQueuedObjectCount() const
  {
    return numQueuedObjects_;
  }

  const ObjectArchetype& Pool::GetSpawnArchetype(const std::string& name) const
  {
    return spawnArchetypes_.at(name);
  }

  void Pool::ShiftQueuedObjects(unsigned numberOfPlaces)
  {
    unsigned firstQueuedObjectIndex = numActiveObjects_;
    unsigned lastQueuedObjectIndex = numActiveObjects_ + numQueuedObjects_ - 1;

    for (auto it = componentArrays_.begin(); it != componentArrays_.end(); ++it)
    {
      ComponentArray* componentArray = it->second;

      for (unsigned i = lastQueuedObjectIndex; i >= firstQueuedObjectIndex; --i)
      {
        componentArray->CopyToThis(*componentArray, i, i + numberOfPlaces);
      }
    }
  }

  void Pool::CreateObjectsInternal(const ObjectArchetype& archetype, unsigned index, unsigned numObjects)
  {
    for (auto it = componentArrays_.begin(); it != componentArrays_.end(); ++it)
    {
      ComponentArray* destination_array = it->second;
      ComponentArray* source_component = archetype.componentArrays_.at(it->first);

      for (unsigned i = 0; i < numObjects; ++i)
      {
        destination_array->CopyToThis(*source_component, 0, index + i);
      }
    }
  }
}