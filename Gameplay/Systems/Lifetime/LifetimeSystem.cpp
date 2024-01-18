/* ======================================================================== */
/*!
 * \file            LifetimeSystem.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Handles game object movement.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "LifetimeSystem.hpp"

#include "ComponentArrays/Destructible/DestructibleArray.hpp"
#include "ComponentArrays/Lifetime/LifetimeArray.hpp"

namespace Barrage
{
  static const std::string BASIC_LIFETIME_POOLS("Basic Lifetime Pools");
  
  LifetimeSystem::LifetimeSystem() :
    System()
  {
    PoolType basic_lifetime_type;
    basic_lifetime_type.AddComponentArray("Lifetime");
    basic_lifetime_type.AddComponentArray("Destructible");
    poolTypes_[BASIC_LIFETIME_POOLS] = basic_lifetime_type;
  }

  void LifetimeSystem::Update()
  {
    UpdatePoolGroup(BASIC_LIFETIME_POOLS, UpdateLifetimes);
  }

  void LifetimeSystem::UpdateLifetimes(Space& space, Pool& pool)
  {
    LifetimeArray& lifetime_array = pool.GetComponentArray<Lifetime>("Lifetime");
    DestructibleArray& destructible_array = pool.GetComponentArray<Destructible>("Destructible");

    unsigned num_objects = pool.ActiveObjectCount();

    for (unsigned i = 0; i < num_objects; ++i)
    {
      Lifetime& lifetime = lifetime_array.Data(i);

      lifetime.ticks_--;

      if (lifetime.ticks_ <= 0)
      {
        destructible_array.Data(i).destroyed_ = true;
      }
    }
  }
}