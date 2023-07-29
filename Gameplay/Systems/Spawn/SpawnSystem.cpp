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
#include "ComponentArrays/SpawnTimerArray.hpp"
#include "Spaces/Space.hpp"
#include <algorithm>

namespace Barrage
{
  static const std::string_view SPAWNER_POOLS("Spawner Pools");
  static const std::string_view SPAWN_TIMER_POOLS("Spawn Timer Pools");
  
  SpawnSystem::SpawnSystem() :
    System()
  {
    PoolType spawner_type;
    spawner_type.AddComponent("Spawner");
    spawner_type.AddComponentArray("SpawnTimer");
    poolTypes_[SPAWNER_POOLS] = spawner_type;

    PoolType spawn_timer_type;
    spawn_timer_type.AddComponentArray("SpawnTimer");
    poolTypes_[SPAWN_TIMER_POOLS] = spawn_timer_type;
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
    UpdatePoolGroup(SPAWNER_POOLS, Spawn);
    UpdatePoolGroup(SPAWN_TIMER_POOLS, UpdateSpawnTimers);
  }

  void SpawnSystem::Spawn(Pool* pool)
  {
    Spawner& spawner = pool->GetComponent<Spawner>("Spawner")->Data();
    SpawnTimerArray& spawnTimerArray = *pool->GetComponentArray<SpawnTimer>("SpawnTimer");
    SpawnPattern& currentPattern = spawner.patterns_.at(spawner.currentPattern_);

    unsigned numObjects = pool->GetActiveObjectCount();

    for (unsigned i = 0; i < numObjects; ++i)
    {
      const unsigned currentTick = spawnTimerArray.Data(i).ticks_;

      SpawnSequence& spawnSequence = currentPattern.spawnSequence_;

      if (spawnSequence.count(currentTick))
      {
        SpawnTypeList& spawnTypeList = spawnSequence.at(currentTick);

        for (auto it = spawnTypeList.spawnTypes_.begin(); it != spawnTypeList.spawnTypes_.end(); ++it)
        {
          SpawnInfo& spawnType = spawner.spawnTypes_.at(*it);

          spawnType.sourceIndices_.push_back(i);
          spawnType.destinationPool_->QueueSpawns(pool, spawnType);
        }
      }

      std::vector<AutomaticSpawn>& automaticSpawns = currentPattern.automaticSpawns_;

      for (auto it = automaticSpawns.begin(); it != automaticSpawns.end(); ++it)
      {
        if (it->ticksPerSpawn_ && currentTick >= it->delay_ && (currentTick - it->delay_) % it->ticksPerSpawn_ == 0)
        {
          SpawnInfo& spawnType = spawner.spawnTypes_.at(it->spawnType_);

          spawnType.sourceIndices_.resize(spawnType.sourceIndices_.size() + it->numberPerBurst_, i);
          spawnType.destinationPool_->QueueSpawns(pool, spawnType);
        }
      }
    }
  }

  void SpawnSystem::UpdateSpawnTimers(Pool* pool)
  {
    SpawnTimerArray& spawnTimerArray = *pool->GetComponentArray<SpawnTimer>("SpawnTimer");

    unsigned numObjects = pool->GetActiveObjectCount();

    for (unsigned i = 0; i < numObjects; ++i)
    {
      spawnTimerArray.Data(i).ticks_++;
    }
  }

  void SpawnSystem::LinkAndValidateSpawns(Pool* pool)
  {
    ObjectManager& objectManager = pool->GetSpace().GetObjectManager();
    Spawner& spawner = pool->GetComponent<Spawner>("Spawner")->Data();

    //
    // make sure all spawn types have a valid destination pool and spawn archetype
    //

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

      spawnType.sourceIndices_.reserve(spawnType.destinationPool_->GetCapacity());

      ++it;
    }

    //
    // remove all spawns referencing a nonexistent spawn type
    //

    for (auto it = spawner.patterns_.begin(); it != spawner.patterns_.end(); ++it)
    {
      SpawnPattern& spawnPattern = it->second;

      SpawnSequence& spawnSequence = spawnPattern.spawnSequence_;

      for (auto jt = spawnSequence.begin(); jt != spawnSequence.end(); ++jt)
      {
        std::vector<std::string>& spawnTypeNames = jt->second.spawnTypes_;

        auto spawnTypeDoesntExist = [&spawnTypes](const std::string& str) {
          return spawnTypes.count(str) == 0;
        };

        spawnTypeNames.erase(std::remove_if(spawnTypeNames.begin(), spawnTypeNames.end(), spawnTypeDoesntExist), spawnTypeNames.end());
      }

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
  }
}