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
    UpdatePoolGroup(BULLET_SPAWNER_POOLS, UpdateBulletSpawners);
  }

  void SpawnSystem::UpdateBulletSpawners(Barrage::Pool* pool)
  {
    Barrage::Spawner& spawner = *pool->GetSharedComponent<Barrage::Spawner>("Spawner");

    spawner.spawnTypes_[0].spawnNum_ = 100;
    spawner.spawnTypes_[0].sourceIndices_.resize(100, 0);
  }
}