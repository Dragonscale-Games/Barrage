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

namespace Demo
{
  static const unsigned BULLET_SPAWNER_POOLS = 0;
  
  SpawnSystem::SpawnSystem() :
    System()
  {
    Barrage::PoolType bullet_type;
    bullet_type.AddTag("Spawner");
    bullet_type.AddComponentName("Spawner");
    poolTypes_[BULLET_SPAWNER_POOLS] = bullet_type;
  }

  void SpawnSystem::Update()
  {
    auto pool_group = pools_.equal_range(BULLET_SPAWNER_POOLS);

    for (auto it = pool_group.first; it != pool_group.second; ++it)
    {
      Barrage::Pool* pool = (*it).second;
      Barrage::Spawner& spawner = *pool->GetSharedComponent<Barrage::Spawner>("Spawner");
      spawner.spawnTypes_["Bullet Spawn"].sourceIndices_.resize(100, 0);
      Barrage::CreationSystem* creation_system = dynamic_cast<Barrage::CreationSystem*>(systemManager_->GetSystem("CreationSystem"));
      creation_system->QueueSpawns(pool, spawner.spawnTypes_["Bullet Spawn"]);
    }
  }
}