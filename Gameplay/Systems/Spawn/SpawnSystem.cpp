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

namespace Barrage
{
  SpawnSystem::SpawnSystem() :
    System()
  {
    PoolType bullet_spawner_type;
    bullet_spawner_type.AddTag("Spawner");
    bullet_spawner_type.AddComponent("Spawner");
    poolTypes_["Bullet Spawner Pools"] = bullet_spawner_type;

    PoolType bullet_pool_type;
    bullet_pool_type.AddTag("Bullet Pool");
    poolTypes_["Bullet Pools"] = bullet_pool_type;
  }

  void SpawnSystem::Update()
  {
    UpdateInteraction("Bullet Spawner Pools", "Bullet Pools", SpawnSystem::SpawnBullets);
  }

  void SpawnSystem::SpawnBullets(Barrage::Pool* spawnerPool, Barrage::Pool* bulletPool)
  {
    Spawner& spawner = spawnerPool->GetComponent<Spawner>("Spawner")->Data();
    
    if (spawner.spawnTypes_.count(0))
    {
      spawner.spawnTypes_[0].sourceIndices_.resize(100, 0);
      bulletPool->QueueSpawns(spawnerPool, spawner.spawnTypes_[0]);
    }
  }
}