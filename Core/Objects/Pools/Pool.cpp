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
    components_(),
    componentArrays_(),
    spawnArchetypes_(),
    tags_(),
    numActiveObjects_(0),
    numQueuedObjects_(0),
    numInitializingObjects_(0),
    capacity_(capacity),
    name_(name),
    space_(space)
  {
  }

  Pool::~Pool()
  {
    // deallocate components
    for (auto it = components_.begin(); it != components_.end(); ++it)
    {
      delete it->second;
    }
    
    // deallocate component arrays
    for (auto it = componentArrays_.begin(); it != componentArrays_.end(); ++it)
    {
      delete it->second;
    }
  }

  void Pool::AddTag(const std::string_view& name)
  {
    tags_.insert(name);
  }

  void Pool::AddComponent(const std::string_view& name, Component* initializer)
  {
    if (components_.count(name))
    {
      return;
    }

    Component* newComponent = ComponentAllocator::AllocateComponent(name, initializer);
    components_[name] = newComponent;
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

  void Pool::AddSpawnArchetype(const ObjectArchetype& spawnArchetype)
  {
    const std::string& name = spawnArchetype.GetName();
    
    if (spawnArchetypes_.count(name))
    {
      return;
    }

    spawnArchetypes_.insert(std::make_pair(name, spawnArchetype));
  }

  void Pool::QueueSpawns(Pool* sourcePool, SpawnInfo& spawnInfo)
  {
    unsigned numObjects = static_cast<unsigned>(spawnInfo.sourceIndices_.size());
    unsigned availableSlots = GetAvailableSlots();

    if (numObjects > availableSlots)
    {
      numObjects = availableSlots;
    }

    if (numObjects != 0)
    {
      unsigned startIndex = GetFirstAvailableSlotIndex();

      CreateObjectsInternal(*spawnInfo.spawnArchetype_, startIndex, numObjects);
      numInitializingObjects_ += numObjects;

      ApplySpawnRules(sourcePool, spawnInfo, startIndex);
    }

    QueueInitializedObjects();

    spawnInfo.sourceIndices_.clear();
  }
  
  void Pool::SpawnObjects()
  {
    numActiveObjects_ += numQueuedObjects_;
    numQueuedObjects_ = 0;
  }

  void Pool::CreateObject(const ObjectArchetype& archetype)
  {
    unsigned availableSlots = GetAvailableSlots();

    if (availableSlots == 0)
    {
      return;
    }

    ShiftInactiveObjects(1);

    unsigned startIndex = numActiveObjects_;

    CreateObjectsInternal(archetype, startIndex, 1);
    numActiveObjects_++;
  }

  Pool::DuplicationResult Pool::DuplicateObject(unsigned numDuplicates, unsigned objectIndex, unsigned sourceIndex, std::vector<unsigned>& sourceIndices)
  {
    unsigned availableSlots = GetAvailableSlots();

    if (numDuplicates > availableSlots)
    {
      numDuplicates = availableSlots;
    }

    unsigned startIndex = GetFirstAvailableSlotIndex();

    DuplicateObjectInternal(objectIndex, startIndex, numDuplicates);
    numInitializingObjects_ += numDuplicates;

    sourceIndices.insert(sourceIndices.end(), numDuplicates, sourceIndex);

    return DuplicationResult(startIndex, numDuplicates);
  }

  bool Pool::HasTag(const std::string_view& tag) const
  {
    return tags_.count(tag);
  }

  bool Pool::HasComponent(const std::string_view& componentName)
  {
    return components_.count(componentName);
  }

  bool Pool::HasComponentArray(const std::string_view& componentArrayName)
  {
    return componentArrays_.count(componentArrayName);
  }

  bool Pool::HasSpawnArchetype(const std::string& name)
  {
    return spawnArchetypes_.count(name);
  }

  unsigned Pool::GetAvailableSlots() const
  {
    return capacity_ - GetFirstAvailableSlotIndex();
  }

  unsigned Pool::GetFirstAvailableSlotIndex() const
  {
    return numActiveObjects_ + numQueuedObjects_ + numInitializingObjects_;
  }

  unsigned Pool::GetActiveObjectCount() const
  {
    return numActiveObjects_;
  }

  unsigned Pool::GetCapacity() const
  {
    return capacity_;
  }

  ComponentArrayMap& Pool::GetComponentArrays()
  {
    return componentArrays_;
  }

  ObjectArchetype* Pool::GetSpawnArchetype(const std::string& name)
  {
    if (spawnArchetypes_.count(name))
    {
      return &spawnArchetypes_.at(name);
    }
    else
    {
      return nullptr;
    }
  }

  SpawnArchetypeMap& Pool::GetSpawnArchetypes()
  {
    return spawnArchetypes_;
  }

  Space& Pool::GetSpace()
  {
    return space_;
  }

  void Pool::ShiftInactiveObjects(unsigned numberOfPlaces)
  {
    if (numQueuedObjects_ == 0 && numInitializingObjects_ == 0)
    {
      return;
    }
    
    unsigned firstInactiveObjectIndex = numActiveObjects_;
    unsigned lastInactiveObjectIndex = GetFirstAvailableSlotIndex() - 1;

    for (auto it = componentArrays_.begin(); it != componentArrays_.end(); ++it)
    {
      ComponentArray* componentArray = it->second;

      for (unsigned i = lastInactiveObjectIndex; i >= firstInactiveObjectIndex; --i)
      {
        componentArray->CopyToThis(*componentArray, i, i + numberOfPlaces);
      }
    }
  }

  void Pool::QueueInitializedObjects()
  {
    numQueuedObjects_ += numInitializingObjects_;
    numInitializingObjects_ = 0;
  }

  void Pool::CreateObjectsInternal(const ObjectArchetype& archetype, unsigned startIndex, unsigned numObjects)
  {
    for (auto it = componentArrays_.begin(); it != componentArrays_.end(); ++it)
    {
      ComponentArray* destination_array = it->second;
      const ComponentArray* source_component = archetype.GetComponentArrays().at(it->first);

      for (unsigned i = 0; i < numObjects; ++i)
      {
        destination_array->CopyToThis(*source_component, 0, startIndex + i);
      }
    }
  }

  void Pool::DuplicateObjectInternal(unsigned objectIndex, unsigned startIndex, unsigned numDuplicates)
  {
    for (auto it = componentArrays_.begin(); it != componentArrays_.end(); ++it)
    {
      ComponentArray* componentArray = it->second;
    
      for (unsigned i = 0; i < numDuplicates; ++i)
      {
        componentArray->CopyToThis(*componentArray, objectIndex, startIndex + i);
      }
    }
  }

  void Pool::ApplySpawnRules(Pool* sourcePool, SpawnInfo& spawnInfo, unsigned startIndex)
  {
    for (auto it = spawnInfo.spawnRules_.begin(); it != spawnInfo.spawnRules_.end(); ++it)
    {
      std::shared_ptr<SpawnRule>& spawnRule = *it;
      
      spawnRule->Execute(*sourcePool, *this, startIndex, numInitializingObjects_, spawnInfo.sourceIndices_);
    }
  }
}