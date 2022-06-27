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
  static const unsigned BASIC_SPAWNER_POOLS = 0;
  
  CreationSystem::CreationSystem() :
    System(),
    archetypeManager_(nullptr),
    spawnFuncManager_(nullptr),
    poolManager_(nullptr)
  {
    PoolType spawner_type;
    spawner_type.AddComponentName("Spawner");
    poolTypes_[BASIC_SPAWNER_POOLS] = spawner_type;
  }

  void CreationSystem::Subscribe(Pool* pool)
  {
    size_t num_pool_types = poolTypes_.size();

    for (size_t i = 0; i < num_pool_types; ++i)
    {
      if (poolTypes_[i].MatchesPool(pool))
      {
        if (i == 0)
        {
          Spawner* spawner = pool->GetSharedComponent<Spawner>("Spawner");
          std::vector<SpawnType>& spawn_types = spawner->spawnTypes_;

          for (auto it = spawn_types.begin(); it != spawn_types.end(); ++it)
          {
            SpawnType& spawn_type = *it;

            spawn_type.sourceIndices_.clear();
          }
        }
        
        pools_.insert(std::pair<unsigned, Pool*>(static_cast<unsigned>(i), pool));
      }
    }
  }

  void CreationSystem::Update()
  {
    auto pool_group = pools_.equal_range(BASIC_SPAWNER_POOLS);

    for (auto it = pool_group.first; it != pool_group.second; ++it)
    {
      UpdateSpawners((*it).second);
    }
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

  void CreationSystem::CreateObject(const ObjectArchetype& archetype, Pool* pool)
  {
    CreateObjects(archetype, pool, 1);
  }
  
  void CreationSystem::CreateObjects(const ObjectArchetype& archetype, Pool* pool, unsigned numNewObjects)
  {
    unsigned available_slots = pool->capacity_ - pool->size_;

    if (available_slots < numNewObjects)
    {
      numNewObjects = available_slots;
    }

    if (numNewObjects == 0)
    {
      return;
    }

    auto begin_it = pool->componentArrays_.begin();
    auto end_it = pool->componentArrays_.end();

    for (auto it = begin_it; it != end_it; ++it)
    {
      ComponentArray* destination_array = it->second;
      ComponentArray* source_component = archetype.components_.at(it->first);

      for (unsigned i = 0; i < numNewObjects; ++i)
      {
        destination_array->CopyToThis(*source_component, 0, pool->size_ + i);
      }
    }

    pool->size_ += numNewObjects;
  }

  void CreationSystem::ApplySpawnFuncs(const std::vector<std::string>& spawnFuncs, Pool* initPool, Pool* destPool, unsigned startIndex, unsigned numObjects, const std::vector<unsigned>& sourceIndices)
  {
    if (numObjects == 0)
      return;

    size_t num_spawn_funcs = spawnFuncs.size();

    for (size_t i = 0; i < num_spawn_funcs; ++i)
    {
      SpawnFunc spawn_func = spawnFuncManager_->GetSpawnFunc(spawnFuncs[i]);

      if (spawn_func)
      {
        spawn_func(*initPool, *destPool, startIndex, numObjects, sourceIndices);
      }
    }
  }

  void CreationSystem::UpdateSpawners(Pool* pool)
  {
    Spawner* spawner = static_cast<Spawner*>(pool->sharedComponents_["Spawner"]);
    
    size_t num_spawn_types = spawner->spawnTypes_.size();

    for (size_t i = 0; i < num_spawn_types; ++i)
    {
      SpawnType& spawn_type = spawner->spawnTypes_[i];

      Pool* destination_pool = poolManager_->GetPool(spawn_type.poolName_);
      ObjectArchetype* object_archetype = archetypeManager_->GetObjectArchetype(spawn_type.archetypeName_);
      unsigned num_new_objects = spawn_type.spawnNum_;
      unsigned available_slots = destination_pool->capacity_ - destination_pool->size_;
      unsigned first_obj_index = destination_pool->size_;

      if (available_slots < num_new_objects)
      {
        num_new_objects = available_slots;
      }

      CreateObjects(*object_archetype, destination_pool, num_new_objects);

      ApplySpawnFuncs(spawn_type.spawnFuncs_, pool, destination_pool, first_obj_index, num_new_objects, spawn_type.sourceIndices_);

      spawn_type.spawnNum_ = 0;
      spawn_type.sourceIndices_.clear();
    }
  }
}