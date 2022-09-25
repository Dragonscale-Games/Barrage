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
    auto pool_group = pools_.equal_range(BULLET_SPAWNER_POOLS);

    for (auto it = pool_group.first; it != pool_group.second; ++it)
    {
      Pool* pool = (*it).second;
      Spawner& spawner = *pool->GetSharedComponent<Spawner>("Spawner");
      spawner.spawnTypes_["Bullet Spawn"].sourceIndices_.resize(100, 0);
      CreationSystem* creation_system = dynamic_cast<CreationSystem*>(systemManager_->GetSystem("CreationSystem"));
      creation_system->QueueSpawns(pool, spawner.spawnTypes_["Bullet Spawn"]);
    }
  }
}