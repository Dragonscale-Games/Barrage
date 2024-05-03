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
#include "Components/Spawner/Spawner.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"
#include "Spaces/Space.hpp"
#include <algorithm>
#include <glm/glm.hpp>

namespace Barrage
{
  static const std::string ALL_POOLS("All Pools");
  static const std::string SPAWNER_POOLS("Spawner Pools");
  
  SpawnSystem::SpawnSystem() :
    System()
  {
    PoolType all_pool_type;
    poolTypes_[ALL_POOLS] = all_pool_type;
    
    PoolType spawner_type;
    spawner_type.AddComponent("Spawner");
    poolTypes_[SPAWNER_POOLS] = spawner_type;
  }

  void SpawnSystem::Subscribe(Space& space, Pool* pool)
  {
    for (auto it = poolTypes_.begin(); it != poolTypes_.end(); ++it)
    {
      PoolType& pool_type = it->second;

      if (pool_type.MatchesPool(pool))
      {
        if (it->first == SPAWNER_POOLS)
        {
          LinkAndValidateSpawns(space, pool);
        }

        poolGroups_[it->first].push_back(pool);
      }
    }
  }

  void SpawnSystem::Update()
  {
    UpdatePoolGroup(SPAWNER_POOLS, UpdateAutomaticSpawns);
    UpdatePoolGroup(SPAWNER_POOLS, UpdateSpawnTimers);
    UpdatePoolGroup(ALL_POOLS, SpawnObjects);
  }

  void SpawnSystem::UpdateAutomaticSpawns(Space& space, Pool& pool)
  {
    Spawner& spawner = pool.GetComponent<Spawner>("Spawner").Data();
    SpawnPattern& currentPattern = spawner.patterns_.at(spawner.currentPattern_);
    std::vector<AutomaticSpawn>& automaticSpawns = currentPattern.automaticSpawns_;
    unsigned numObjects = pool.ActiveObjectCount();

    for (auto it = automaticSpawns.begin(); it != automaticSpawns.end(); ++it)
    {
      SpawnType& spawnType = spawner.spawnTypes_.at(it->spawnType_);
      
      for (unsigned i = 0; i < numObjects; ++i)
      {
        const unsigned currentTick = spawner.spawnTimers_.Data(i);

        if (it->ticksPerSpawn_ && currentTick >= it->delay_ && (currentTick - it->delay_) % it->ticksPerSpawn_ == 0)
        {
          spawnType.CreateSpawn(i);
        }
        else if (it->ticksPerSpawn_ == 0 && currentTick == it->delay_)
        {
          spawnType.CreateSpawn(i);
        }
      }

      Pool& destinationPool = space.Objects().pools_.at(spawnType.destinationPool_);
      destinationPool.QueueSpawns(space, pool, spawnType);
    }
  }

  void SpawnSystem::UpdateSpawnTimers(Space& space, Pool& pool)
  {
    Spawner& spawner = pool.GetComponent<Spawner>("Spawner").Data();

    unsigned numObjects = pool.ActiveObjectCount();

    for (unsigned i = 0; i < numObjects; ++i)
    {
      spawner.spawnTimers_.Data(i)++;
    }
  }

  void SpawnSystem::SpawnObjects(Space& space, Pool& pool)
  {
    pool.SpawnObjects();
  }

  void SpawnSystem::LinkAndValidateSpawns(Space& space, Pool* pool)
  {
    ObjectManager& objectManager = space.Objects();
    Spawner& spawner = pool->GetComponent<Spawner>("Spawner").Data();

    //
    // validate all spawn types
    //

    SpawnTypeMap& spawnTypes = spawner.spawnTypes_;

    for (auto it = spawnTypes.begin(); it != spawnTypes.end(); /* iterator updated in body */)
    {
      SpawnType& spawnType = it->second;

      // make sure spawn type has a valid destination pool
      if (objectManager.pools_.count(spawnType.destinationPool_) == 0)
      {
        it = spawnTypes.erase(it);
        continue;
      }

      Pool& destinationPool = objectManager.pools_.at(spawnType.destinationPool_);

      // make sure spawn type has a valid spawn archetype
      if (destinationPool.spawnArchetypes_.count(spawnType.spawnArchetype_) == 0)
      {
        it = spawnTypes.erase(it);
        continue;
      }

      ++it;
    }

    //
    // remove all spawns referencing a nonexistent spawn type
    //

    for (auto it = spawner.patterns_.begin(); it != spawner.patterns_.end(); ++it)
    {
      SpawnPattern& spawnPattern = it->second;

      std::vector<AutomaticSpawn>& automaticSpawns = spawnPattern.automaticSpawns_;

      for (auto jt = automaticSpawns.begin(); jt != automaticSpawns.end(); /* iterator updated in body */)
      {
        if (spawnTypes.count(jt->spawnType_) == 0)
        {
          jt = automaticSpawns.erase(jt);
        }
        else
        {
          ++jt;
        }
      }
    }

    //
    // if current pattern doesn't exist, create a dummy pattern
    //

    if (spawner.patterns_.count(spawner.currentPattern_) == 0)
    {
      spawner.patterns_[spawner.currentPattern_];
    }
  }
}