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
#include "ComponentArrays/DestructibleArray.hpp"
#include "Components/Spawner.hpp"

namespace Barrage
{
  static const std::string_view BASIC_DESTRUCTIBLE_POOLS("Basic Destructible Pools");
  static const std::string_view DESTRUCTIBLE_SPAWNER_POOLS("Destructible Spawner Pools");
  
  DestructionSystem::DestructionSystem() :
    System()
  {
    PoolType basic_destructible_type;
    basic_destructible_type.AddComponentArray("Destructible");
    poolTypes_[BASIC_DESTRUCTIBLE_POOLS] = basic_destructible_type;

    PoolType destructible_spawner_type;
    destructible_spawner_type.AddComponentArray("Destructible");
    destructible_spawner_type.AddComponent("Spawner");
    poolTypes_[DESTRUCTIBLE_SPAWNER_POOLS] = destructible_spawner_type;
  }
  
  void DestructionSystem::Update()
  {
    UpdatePoolGroup(DESTRUCTIBLE_SPAWNER_POOLS, UpdateSpawnRules);
    UpdatePoolGroup(BASIC_DESTRUCTIBLE_POOLS, DestroyObjects);
  }

  void DestructionSystem::UpdateSpawnRules(Pool* pool)
  {
    Spawner& spawner = pool->GetComponent<Spawner>("Spawner")->Data();
    DestructibleArray& destructibleArray = *pool->GetComponentArray<Destructible>("Destructible");
    const bool* destructiblesRaw = reinterpret_cast<bool*>(&destructibleArray.Data(0));
    unsigned numActiveObjects = pool->GetActiveObjectCount();
    unsigned deadBeginIndex = GetFirstDeadObjectIndex(destructiblesRaw, numActiveObjects);
    
    // if no objects were destroyed, early out
    if (deadBeginIndex >= numActiveObjects)
      return;

    for (auto it = spawner.spawnTypes_.begin(); it != spawner.spawnTypes_.end(); ++it)
    {
      SpawnInfo& spawnType = it->second;

      for (auto jt = spawnType.spawnRulesWithArrays_.begin(); jt != spawnType.spawnRulesWithArrays_.end(); ++jt)
      {
        std::shared_ptr<SpawnRuleWithArray>& spawnRuleWithArray = *jt;

        spawnRuleWithArray->HandleDestructions(destructiblesRaw, deadBeginIndex, numActiveObjects);
      }
    }
  }

  void DestructionSystem::DestroyObjects(Pool* pool)
  {
    DestructibleArray& destructibleArray = *pool->GetComponentArray<Destructible>("Destructible");
    const bool* destructiblesRaw = reinterpret_cast<bool*>(&destructibleArray.Data(0));
    unsigned numActiveObjects = pool->GetActiveObjectCount();
    unsigned deadBeginIndex = GetFirstDeadObjectIndex(destructiblesRaw, numActiveObjects);

    // if no objects were destroyed, early out
    if (deadBeginIndex >= numActiveObjects)
      return;

    for (auto it = pool->componentArrays_.begin(); it != pool->componentArrays_.end(); ++it)
    {
      // we'll operate on the destructible array last; after the loop finishes
      if (it->first == "Destructible")
        continue;

      it->second->HandleDestructions(destructiblesRaw, deadBeginIndex, numActiveObjects);
    }

    // operate on the destructibles array last and update the number of alive objects in the pool
    pool->numActiveObjects_ = destructibleArray.HandleDestructions(destructiblesRaw, deadBeginIndex, numActiveObjects);
  }

  unsigned DestructionSystem::GetFirstDeadObjectIndex(const bool* destructiblesArray, unsigned numElements)
  {
    unsigned index = 0;

    while (index < numElements)
    {
      if (destructiblesArray[index] == true)
      {
        break;
      }
        
      ++index;
    }

    return index;
  }
}