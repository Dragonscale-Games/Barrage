/* ======================================================================== */
/*!
 * \file            DestructionSystem.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Handles destruction for all destructible objects. All destroyed objects
   are lazy deleted, then all remaining active objects are sorted to the
   front of the pool and the active object count is updated.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "DestructionSystem.hpp"
#include "ComponentArrays/Destructible/DestructibleArray.hpp"
#include "Components/Spawner/Spawner.hpp"
#include "Components/Behavior/Behavior.hpp"

namespace Barrage
{
  static const std::string BASIC_DESTRUCTIBLE_POOLS("Basic Destructible Pools");
  static const std::string DESTRUCTIBLE_SPAWNER_POOLS("Destructible Spawner Pools");
  static const std::string DESTRUCTIBLE_BEHAVIOR_POOLS("Destructible Behavior Pools");
  
  DestructionSystem::DestructionSystem() :
    System()
  {
    PoolType basic_destructible_type;
    basic_destructible_type.AddComponentArray("Destructible");
    poolTypes_[BASIC_DESTRUCTIBLE_POOLS] = basic_destructible_type;

    PoolType destructible_spawner_type;
    destructible_spawner_type.AddComponent("Spawner");
    destructible_spawner_type.AddComponentArray("Destructible");
    poolTypes_[DESTRUCTIBLE_SPAWNER_POOLS] = destructible_spawner_type;

    PoolType destructible_behavior_type;
    destructible_behavior_type.AddComponent("BehaviorTree");
    destructible_behavior_type.AddComponentArray("Destructible");
    poolTypes_[DESTRUCTIBLE_BEHAVIOR_POOLS] = destructible_behavior_type;
  }
  
  void DestructionSystem::Update()
  {
    UpdatePoolGroup(DESTRUCTIBLE_BEHAVIOR_POOLS, UpdateBehaviorPools);
    UpdatePoolGroup(DESTRUCTIBLE_SPAWNER_POOLS, UpdateSpawnRules);
    UpdatePoolGroup(BASIC_DESTRUCTIBLE_POOLS, DestroyObjects);
  }

  void DestructionSystem::UpdateBehaviorPools(Space& space, Pool& pool)
  {
    BehaviorTree& behaviorTree = pool.GetComponent<BehaviorTree>("BehaviorTree").Data();
    DestructibleArray& destructibleArray = pool.GetComponentArray<Destructible>("Destructible");
    unsigned numActiveObjects = pool.ActiveObjectCount();
    unsigned deadBeginIndex = GetFirstDeadObjectIndex(destructibleArray, numActiveObjects);

    // if no objects were destroyed, early out
    if (deadBeginIndex >= numActiveObjects)
      return;

    behaviorTree.HandleDestructions(destructibleArray.GetRaw(), deadBeginIndex, numActiveObjects);
  }

  void DestructionSystem::UpdateSpawnRules(Space& space, Pool& pool)
  {
    Spawner& spawner = pool.GetComponent<Spawner>("Spawner").Data();
    DestructibleArray& destructibleArray = pool.GetComponentArray<Destructible>("Destructible");
    unsigned numActiveObjects = pool.ActiveObjectCount();
    unsigned deadBeginIndex = GetFirstDeadObjectIndex(destructibleArray, numActiveObjects);
    
    // if no objects were destroyed, early out
    if (deadBeginIndex >= numActiveObjects)
      return;

    for (auto it = spawner.spawnTypes_.begin(); it != spawner.spawnTypes_.end(); ++it)
    {
      SpawnType& spawnType = it->second;

      spawnType.HandleDestructions(destructibleArray.GetRaw(), deadBeginIndex, numActiveObjects);
    }
  }

  void DestructionSystem::DestroyObjects(Space& space, Pool& pool)
  {
    DestructibleArray& destructibleArray = pool.GetComponentArray<Destructible>("Destructible");
    unsigned numActiveObjects = pool.ActiveObjectCount();
    unsigned deadBeginIndex = GetFirstDeadObjectIndex(destructibleArray, numActiveObjects);

    // if no objects were destroyed, early out
    if (deadBeginIndex >= numActiveObjects)
      return;

    for (auto it = pool.componentArrays_.begin(); it != pool.componentArrays_.end(); ++it)
    {
      // we'll operate on the destructible array last; after the loop finishes
      if (it->first == "Destructible")
        continue;

      it->second->HandleDestructions(destructibleArray.GetRaw(), deadBeginIndex, numActiveObjects);
    }

    // operate on the destructibles array last and update the number of alive objects in the pool
    pool.numActiveObjects_ = destructibleArray.HandleDestructions(destructibleArray.GetRaw(), deadBeginIndex, numActiveObjects);
  }

  unsigned DestructionSystem::GetFirstDeadObjectIndex(DestructibleArray& destructiblesArray, unsigned numElements)
  {
    unsigned index = 0;

    while (index < numElements)
    {
      if (destructiblesArray.Data(index).destroyed_ == true)
      {
        break;
      }
        
      ++index;
    }

    return index;
  }
}