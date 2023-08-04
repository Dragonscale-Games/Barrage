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
#include "ComponentArrays/VelocityArray.hpp"
#include "Spaces/Space.hpp"
#include <algorithm>
#include <glm/glm.hpp>

namespace Barrage
{
  static const std::string_view SPAWNER_POOLS("Spawner Pools");
  static const std::string_view SPAWN_TIMER_POOLS("Spawn Timer Pools");
  static const std::string_view VELOCITY_POOLS("Velocity Pools");
  
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

    PoolType velocity_type;
    velocity_type.AddComponentArray("Velocity");
    poolTypes_[VELOCITY_POOLS] = velocity_type;
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
        else if (it->first == VELOCITY_POOLS)
        {
          MakeSpawnVelocitiesNonZero(pool);
          continue; // we don't need to store these pools
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
    // validate all spawn types
    //

    SpawnTypeMap& spawnTypes = spawner.spawnTypes_;

    for (auto it = spawnTypes.begin(); it != spawnTypes.end(); /* iterator updated in body */)
    {
      SpawnInfo& spawnType = it->second;

      // make sure spawn type has a valid destination pool
      spawnType.destinationPool_ = objectManager.GetPool(spawnType.destinationPoolName_);
      if (spawnType.destinationPool_ == nullptr)
      {
        it = spawnTypes.erase(it);
        continue;
      }

      // make sure spawn type has a valid spawn archetype
      spawnType.spawnArchetype_ = spawnType.destinationPool_->GetSpawnArchetype(spawnType.spawnArchetypeName_);
      if (spawnType.spawnArchetype_ == nullptr)
      {
        it = spawnTypes.erase(it);
        continue;
      }

      // preallocate source index array
      spawnType.sourceIndices_.reserve(spawnType.destinationPool_->GetCapacity());

      // find spawn rules with arrays and allocate them to match pool capacity
      for (auto& spawnRule : spawnType.spawnRules_)
      {
        auto spawnRuleWithArray = std::dynamic_pointer_cast<SpawnRuleWithArray>(spawnRule);

        if (spawnRuleWithArray)
        {
          spawnRuleWithArray->SetCapacity(pool->GetCapacity());
          spawnType.spawnRulesWithArrays_.push_back(spawnRuleWithArray);
        }
      }

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

    //
    // if current pattern doesn't exist, create a dummy pattern
    //

    if (spawner.patterns_.count(spawner.currentPattern_) == 0)
    {
      spawner.patterns_[spawner.currentPattern_];
    }
  }

  void SpawnSystem::MakeSpawnVelocitiesNonZero(Pool* pool)
  {
    //
    // spawn archetypes with a velocity of 0 break some spawn rules, so give them a slight magnitude here
    //

    SpawnArchetypeMap& spawnArchetypes = pool->GetSpawnArchetypes();

    for (auto it = spawnArchetypes.begin(); it != spawnArchetypes.end(); ++it)
    {
      ObjectArchetype& spawnArchetype = it->second;
      Velocity& velocity = dynamic_cast<VelocityArray*>(spawnArchetype.GetComponentArray("Velocity"))->Data(0);

      if (glm::length(glm::vec2(velocity.vx_, velocity.vy_)) < MINIMUM_SPEED)
      {
        velocity.vx_ = MINIMUM_SPEED;
        velocity.vy_ = 0.0f;
      }
    }
  }
}