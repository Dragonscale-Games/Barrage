/* ======================================================================== */
/*!
 * \file            CreationSystem.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Handles object creation both directly (through an object creation function)
   and indirectly (through updating object spawners).
 */
/* ======================================================================== */

#include "stdafx.h"
#include "CreationSystem.hpp"

namespace Barrage
{
  static const unsigned ALL_POOLS = 0;
  static const unsigned HANDLE_POOLS = 1;

  CreationSystem::CreationSystem() :
    System(),
    archetypeManager_(nullptr),
    spawnFuncManager_(nullptr),
    poolManager_(nullptr)
  {
    // this pool type has no required tags or components because all pools will be subscribed to the creation system
    PoolType all_pool_type;
    poolTypes_[ALL_POOLS] = all_pool_type;

    PoolType handle_pool_type;
    handle_pool_type.AddSharedComponent("ObjectDirectory");
    handle_pool_type.AddComponentArray("DirectoryIndex");
    poolTypes_[HANDLE_POOLS] = handle_pool_type;
  }

  void CreationSystem::Update()
  {
    UpdatePoolGroup(HANDLE_POOLS, AssignHandles);
    UpdatePoolGroup(ALL_POOLS, SpawnObjects);
  }

  void CreationSystem::SetArchetypeManager(ArchetypeManager& archetypeManager)
  {
    archetypeManager_ = &archetypeManager;
  }

  void CreationSystem::SetSpawnFuncManager(SpawnFuncManager& spawnFuncManager)
  {
    spawnFuncManager_ = &spawnFuncManager;
  }

  void CreationSystem::SetPoolManager(PoolManager& poolManager)
  {
    poolManager_ = &poolManager;
  }

  void CreationSystem::CreateObject(const ObjectArchetype& archetype, Pool* destinationPool)
  {
    unsigned available_slots = destinationPool->GetAvailableSlots();

    if (available_slots == 0)
    {
      return;
    }

    CreateObjects(archetype, destinationPool, 1, false);

    if (destinationPool->HasComponentArray("DirectoryIndexArray") && destinationPool->HasSharedComponent("ObjectDirectory"))
    {
      ObjectDirectory& object_directory = destinationPool->GetSharedComponent<ObjectDirectory>("ObjectDirectory")->Data();
      DirectoryIndexArray& directory_index_array = *destinationPool->GetComponentArray<DirectoryIndex>("DirectoryIndex");

      unsigned object_index = destinationPool->numActiveObjects_ - 1;
      DirectoryIndex& directory_index = directory_index_array.Data(object_index);
      directory_index.index_ = object_directory.CreateHandle(object_index);
    }
  }
  
  void CreationSystem::QueueSpawns(Pool* sourcePool, SpawnType& spawnType)
  {
    ObjectArchetype* object_archetype = archetypeManager_->GetObjectArchetype(spawnType.archetypeName_);
    Pool* destination_pool = poolManager_->GetPool(spawnType.destinationPoolName_);
    unsigned num_spawns = static_cast<unsigned>(spawnType.sourceIndices_.size());
    unsigned available_slots = destination_pool->GetAvailableSlots();
    unsigned start_index = destination_pool->numActiveObjects_ + destination_pool->numQueuedObjects_;

    if (available_slots < num_spawns)
    {
      num_spawns = available_slots;
    }
      
    if (num_spawns != 0)
    {
      CreateObjects(*object_archetype, destination_pool, num_spawns, true);
      ApplySpawnFuncs(spawnType.spawnFuncs_, sourcePool, destination_pool, start_index, num_spawns, spawnType.sourceIndices_);
    }

    spawnType.sourceIndices_.clear();
  }

  void CreationSystem::CreateObjects(const ObjectArchetype& archetype, Pool* destinationPool, unsigned numNewObjects, bool queueObjects)
  {
    auto begin_it = destinationPool->componentArrays_.begin();
    auto end_it = destinationPool->componentArrays_.end();

    for (auto it = begin_it; it != end_it; ++it)
    {
      ComponentArray* destination_array = it->second;
      ComponentArray* source_component = archetype.components_.at(it->first);

      for (unsigned i = 0; i < numNewObjects; ++i)
      {
        destination_array->CopyToThis(*source_component, 0, destinationPool->numActiveObjects_ + destinationPool->numQueuedObjects_ + i);
      }
    }

    if (queueObjects)
    {
      destinationPool->numQueuedObjects_ += numNewObjects;
    }
    else
    {
      destinationPool->numActiveObjects_ += numNewObjects;
    }
  }

  void CreationSystem::ApplySpawnFuncs(const std::vector<std::string>& spawnFuncs, Pool* sourcePool, Pool* destinationPool, unsigned startIndex, unsigned numObjects, const std::vector<unsigned>& sourceIndices)
  {
    size_t num_spawn_funcs = spawnFuncs.size();

    for (size_t i = 0; i < num_spawn_funcs; ++i)
    {
      SpawnFunc spawn_func = spawnFuncManager_->GetSpawnFunc(spawnFuncs[i]);

      if (spawn_func)
      {
        spawn_func(*sourcePool, *destinationPool, startIndex, numObjects, sourceIndices);
      }
    }
  }

  void CreationSystem::SpawnObjects(Pool* pool)
  {
    pool->numActiveObjects_ += pool->numQueuedObjects_;
    pool->numQueuedObjects_ = 0;
  }

  void CreationSystem::AssignHandles(Pool* pool)
  {
    ObjectDirectory& object_directory = pool->GetSharedComponent<ObjectDirectory>("ObjectDirectory")->Data();
    DirectoryIndexArray& directory_index_array = *pool->GetComponentArray<DirectoryIndex>("DirectoryIndex");

    unsigned start_index = pool->numActiveObjects_;
    unsigned num_queued_objects = pool->numQueuedObjects_;

    for (unsigned i = 0; i < num_queued_objects; ++i)
    {
      unsigned object_index = start_index + i;
      
      DirectoryIndex& directory_index = directory_index_array.Data(object_index);

      directory_index.index_ = object_directory.CreateHandle(object_index);
    }
  }
}