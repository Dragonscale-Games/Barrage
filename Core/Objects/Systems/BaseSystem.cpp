/* ======================================================================== */
/*!
 * \file            BaseSystem.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base object system class that all object systems should inherit from.

   An object system is a collection of related functions that perform operations
   on game object components. For instance, a movement system might contain all
   functions that change an object's position component.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "BaseSystem.hpp"

namespace Barrage
{
  System::System() :
    poolTypes_(),
    pools_()
  {
  }

  void System::Subscribe(Pool* pool)
  {
    for (auto it = poolTypes_.begin(); it != poolTypes_.end(); ++it)
    {
      PoolType& pool_type = it->second;
      
      if (pool_type.MatchesPool(pool))
      {
        pools_.insert(std::pair<unsigned, Pool*>(it->first, pool));
      }
    }
  }

  void System::Unsubscribe(Pool* pool)
  {
    for (auto it = pools_.begin(); it != pools_.end(); /* increment handled in body */)
    {
      if (it->second == pool)
      {
        it = pools_.erase(it);
      }
      else
      {
        ++it;
      }
    }
  }

  void System::Update()
  {
    // intentionally empty
  }

  void System::UpdatePoolGroup(unsigned group, PoolUpdateFunc function)
  {
    auto pool_group = pools_.equal_range(group);

    for (auto it = pool_group.first; it != pool_group.second; ++it)
    {
      Pool* pool = (*it).second;
      function(pool);
    }
  }

  void System::UpdateInteraction(unsigned group1, unsigned group2, InteractionFunc function)
  {
    auto pool_group_1 = pools_.equal_range(group1);
    auto pool_group_2 = pools_.equal_range(group2);

    for (auto it = pool_group_1.first; it != pool_group_1.second; ++it)
    {
      for (auto jt = pool_group_2.first; jt != pool_group_2.second; ++jt)
      {
        Pool* pool_1 = (*it).second;
        Pool* pool_2 = (*jt).second;

        function(pool_1, pool_2);
      }
    }
  }
}