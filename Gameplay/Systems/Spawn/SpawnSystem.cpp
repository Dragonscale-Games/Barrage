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
#include "ComponentArrays/SpawnTimer/SpawnTimerArray.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"
#include "Spaces/Space.hpp"
#include <algorithm>
#include <glm/glm.hpp>

namespace Barrage
{
  static const std::string SPAWNER_POOLS("Spawner Pools");
  static const std::string SPAWN_TIMER_POOLS("Spawn Timer Pools");
  static const std::string VELOCITY_POOLS("Velocity Pools");
  
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

  void SpawnSystem::Spawn(Space& space, Pool& pool)
  {
    Spawner& spawner = pool.GetComponent<Spawner>("Spawner").Data();
    SpawnTimerArray& spawnTimerArray = pool.GetComponentArray<SpawnTimer>("SpawnTimer");
    SpawnPattern& currentPattern = spawner.patterns_.at(spawner.currentPattern_);
    std::vector<AutomaticSpawn>& automaticSpawns = currentPattern.automaticSpawns_;
    unsigned numObjects = pool.ActiveObjectCount();

    for (auto it = automaticSpawns.begin(); it != automaticSpawns.end(); ++it)
    {
      SpawnType& spawnType = spawner.spawnTypes_.at(it->spawnType_);
      
      for (unsigned i = 0; i < numObjects; ++i)
      {
        const unsigned currentTick = spawnTimerArray.Data(i).ticks_;

        if (it->ticksPerSpawn_ && currentTick >= it->delay_ && (currentTick - it->delay_) % it->ticksPerSpawn_ == 0)
        {
          spawnType.CreateSpawn(i);
        }
        else if (it->ticksPerSpawn_ == 0 && currentTick == it->delay_)
        {
          spawnType.CreateSpawn(i);
        }
      }

      Pool& destinationPool = space.GetObjectManager().pools_.at(spawnType.destinationPool_);
      destinationPool.QueueSpawns(space, pool, spawnType);
    }
  }

  void SpawnSystem::UpdateSpawnTimers(Space& space, Pool& pool)
  {
    SpawnTimerArray& spawnTimerArray = pool.GetComponentArray<SpawnTimer>("SpawnTimer");

    unsigned numObjects = pool.ActiveObjectCount();

    for (unsigned i = 0; i < numObjects; ++i)
    {
      spawnTimerArray.Data(i).ticks_++;
    }
  }

  void SpawnSystem::LinkAndValidateSpawns(Space& space, Pool* pool)
  {
    ObjectManager& objectManager = space.GetObjectManager();
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

      // preallocate source index array
      spawnType.sourceIndices_.reserve(destinationPool.GetCapacity());

      // allocate spawn type to match pool capacity
      spawnType.SetCapacity(pool->GetCapacity());

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

  void SpawnSystem::MakeSpawnVelocitiesNonZero(Pool* pool)
  {
    //
    // spawn archetypes with a velocity of 0 break some spawn rules, so give them a slight magnitude here
    //

    ObjectArchetypeMap& spawnArchetypes = pool->spawnArchetypes_;

    for (auto it = spawnArchetypes.begin(); it != spawnArchetypes.end(); ++it)
    {
      ObjectArchetype& spawnArchetype = it->second;
      Velocity& velocity = dynamic_cast<VelocityArray&>(*spawnArchetype.componentArrays_.at("Velocity")).Data(0);

      if (glm::length(glm::vec2(velocity.vx_, velocity.vy_)) < MINIMUM_SPEED)
      {
        velocity.vx_ = MINIMUM_SPEED;
        velocity.vy_ = 0.0f;
      }
    }
  }
}