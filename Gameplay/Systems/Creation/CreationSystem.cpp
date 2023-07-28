/* ======================================================================== */
/*!
 * \file            CreationSystem.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Handles object creation both directly (through an object creation function)
   and indirectly (through updating object spawners).
 */
/* ======================================================================== */

#include "stdafx.h"
#include "CreationSystem.hpp"

namespace Barrage
{
  CreationSystem::CreationSystem() :
    System()
  {
    PoolType all_pool_type;
    poolTypes_["All Pools"] = all_pool_type;
  }

  void CreationSystem::Update()
  {
    UpdatePoolGroup("All Pools", SpawnObjects);
  }

  void CreationSystem::SpawnObjects(Pool* pool)
  {
    pool->SpawnObjects();
  }
}