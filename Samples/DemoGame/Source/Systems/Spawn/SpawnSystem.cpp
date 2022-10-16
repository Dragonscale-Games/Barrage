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
#include <Objects/Systems/Creation/CreationSystem.hpp>
#include "../../SpawnTypes.hpp"

namespace Demo
{
  using namespace Barrage;
  
  static const unsigned BULLET_SPAWNER_POOLS = 0;
  
  SpawnSystem::SpawnSystem() :
    System()
  {
    PoolType bullet_type;
    bullet_type.AddTag("Spawner");
    bullet_type.AddComponentName("Spawner");
    poolTypes_[BULLET_SPAWNER_POOLS] = bullet_type;
  }

  void SpawnSystem::Update()
  {
    UpdatePoolGroup(BULLET_SPAWNER_POOLS, static_cast<PoolUpdateMemberFunc>(&SpawnSystem::SpawnBullets));
  }

  void SpawnSystem::SpawnBullets(Pool* pool)
  {
    Spawner& spawner = *pool->GetSharedComponent<Spawner>("Spawner");
    spawner.spawnTypes_[BULLET_SPAWN_TYPE].sourceIndices_.resize(100, 0);
    CreationSystem* creation_system = dynamic_cast<CreationSystem*>(systemManager_->GetSystem("CreationSystem"));
    creation_system->QueueSpawns(pool, spawner.spawnTypes_[BULLET_SPAWN_TYPE]);
  }
}