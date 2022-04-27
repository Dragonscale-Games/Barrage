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
  CreationSystem::CreationSystem() :
    System(),
    archetypeManager_(nullptr),
    initializerManager_(nullptr),
    poolManager_(nullptr)
  {
    systemComponents_.push_back("Spawner");
  }

  void CreationSystem::SetArchetypeManager(ArchetypeManager& archetypeManager)
  {
    archetypeManager_ = &archetypeManager;
  }

  void CreationSystem::SetSpawnFuncManager(SpawnFuncManager& spawnFuncManager)
  {
    initializerManager_ = &spawnFuncManager;
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
    unsigned available_slots = pool->capacity_ - pool->activeObjects_;

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
        destination_array->CopyToThis(*source_component, 0, pool->activeObjects_ + i);
      }
    }

    pool->activeObjects_ += numNewObjects;
  }

  void CreationSystem::ApplySpawnFuncs(const std::vector<SpawnFunc>& spawnFuncs, Pool* initPool, Pool* destPool, unsigned startIndex, unsigned numObjects)
  {
    if (numObjects == 0)
      return;

    size_t num_spawn_funcs = spawnFuncs.size();

    for (size_t i = 0; i < num_spawn_funcs; ++i)
    {
      SpawnFunc spawn_func = spawnFuncs[i];

      if (spawn_func)
      {
        spawn_func(*initPool, *destPool, startIndex, numObjects);
      }
    }
  }

  void CreationSystem::UpdatePool(Pool* pool)
  {
    Spawner* spawner = static_cast<Spawner*>(pool->sharedComponents_["Spawner"]);
    
    size_t num_spawn_types = spawner->spawnTypes_.size();

    for (size_t i = 0; i < num_spawn_types; ++i)
    {
      Spawner::SpawnType& spawn_type = spawner->spawnTypes_[i];

      Pool* destination_pool = poolManager_->GetPool(spawn_type.poolName_);
      ObjectArchetype* object_archetype = archetypeManager_->GetObjectArchetype(spawn_type.archetypeName_);
      unsigned num_new_objects = spawn_type.spawnNum_;
      unsigned available_slots = destination_pool->capacity_ - destination_pool->activeObjects_;
      unsigned first_obj_index = destination_pool->activeObjects_;

      if (available_slots < num_new_objects)
      {
        num_new_objects = available_slots;
      }

      CreateObjects(*object_archetype, destination_pool, num_new_objects);

      ApplySpawnFuncs(spawn_type.spawnFuncs_, pool, destination_pool, first_obj_index, num_new_objects);

      //spawn_type.spawnNum_ = 0;
    }
  }
}