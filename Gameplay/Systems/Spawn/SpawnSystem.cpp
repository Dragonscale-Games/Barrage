/* ======================================================================== */
/*!
 * \file            STUB.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 
 */
/* ======================================================================== */

#include "stdafx.h"
#include "SpawnSystem.hpp"
#include <Objects/Systems/SystemManager.hpp>
#include "Components/Spawner.hpp"
#include "Spaces/Space.hpp"

namespace Barrage
{
  static const std::string_view SPAWNER_POOLS("Spawner Pools");
  
  SpawnSystem::SpawnSystem() :
    System()
  {
    PoolType spawner_type;
    spawner_type.AddComponent("Spawner");
    poolTypes_[SPAWNER_POOLS] = spawner_type;
  }

  void SpawnSystem::Subscribe(Pool* pool)
  {
    for (auto it = poolTypes_.begin(); it != poolTypes_.end(); ++it)
    {
      PoolType& pool_type = it->second;

      if (pool_type.MatchesPool(pool))
      {
        if (it->first == SPAWNER_POOLS)
        {
          LinkAndValidateSpawns(pool);
        }
        
        poolGroups_[it->first].push_back(pool);
      }
    }
  }

  void SpawnSystem::Update()
  {
    
  }

  void SpawnSystem::LinkAndValidateSpawns(Pool* pool)
  {
    ObjectManager& objectManager = pool->GetSpace().GetObjectManager();
    Spawner& spawner = pool->GetComponent<Spawner>("Spawner")->Data();
    SpawnTypeMap& spawnTypes = spawner.spawnTypes_;

    for (auto it = spawnTypes.begin(); it != spawnTypes.end(); /* iterator updated in body */)
    {
      SpawnInfo& spawnType = it->second;

      spawnType.destinationPool_ = objectManager.GetPool(spawnType.destinationPoolName_);
      
      if (spawnType.destinationPool_ == nullptr)
      {
        it = spawnTypes.erase(it);
        continue;
      }

      spawnType.spawnArchetype_ = spawnType.destinationPool_->GetSpawnArchetype(spawnType.spawnArchetypeName_);

      if (spawnType.spawnArchetype_ == nullptr)
      {
        it = spawnTypes.erase(it);
        continue;
      }

      ++it;
    }
  }
}