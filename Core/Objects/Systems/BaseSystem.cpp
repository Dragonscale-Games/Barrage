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
    pools_(),
    systemManager_(nullptr)
  {
  }

  void System::Subscribe(Pool* pool)
  {
    for (auto it = poolTypes_.begin(); it != poolTypes_.end(); ++it)
    {
      PoolType& pool_type = it->second;
      
      if (pool_type.MatchesPool(pool))
      {
        pools_[it->first].push_back(pool);
      }
    }
  }

  void System::Unsubscribe(Pool* pool)
  {
    for (auto it = pools_.begin(); it != pools_.end(); ++it)
    {
      std::vector<Pool*>& pool_group = it->second;

      for (auto jt = pool_group.begin(); jt != pool_group.end(); /* iterator incremented in body */)
      {
        if (*jt == pool)
        {
          jt = pool_group.erase(jt);
        }
        else
        {
          ++jt;
        }
      }
    }
  }

  void System::Update()
  {
    // intentionally empty
  }

  void System::SetSystemManager(SystemManager* manager)
  {
    systemManager_ = manager;
  }

  void System::UpdatePoolGroup(unsigned group, PoolUpdateFunc function)
  {
    std::vector<Pool*>& pool_group = pools_[group];

    for (auto it = pool_group.begin(); it != pool_group.end(); ++it)
    {
      function(*it);
    }
  }

  void System::UpdatePoolGroup(unsigned group, PoolUpdateMemberFunc function)
  {
    std::vector<Pool*>& pool_group = pools_[group];

    for (auto it = pool_group.begin(); it != pool_group.end(); ++it)
    {
      CALL_MEMBER_FN(*this, function)(*it);
    }
  }

  void System::UpdateInteraction(unsigned group1, unsigned group2, InteractionFunc function)
  {
    std::vector<Pool*>& pool_group_1 = pools_[group1];
    std::vector<Pool*>& pool_group_2 = pools_[group2];

    for (auto it = pool_group_1.begin(); it != pool_group_1.end(); ++it)
    {
      for (auto jt = pool_group_2.begin(); jt != pool_group_2.end(); ++jt)
      {
        function(*it, *jt);
      }
    }
  }

  void System::UpdateInteraction(unsigned group1, unsigned group2, InteractionMemberFunc function)
  {
    std::vector<Pool*>& pool_group_1 = pools_[group1];
    std::vector<Pool*>& pool_group_2 = pools_[group2];

    for (auto it = pool_group_1.begin(); it != pool_group_1.end(); ++it)
    {
      for (auto jt = pool_group_2.begin(); jt != pool_group_2.end(); ++jt)
      {
        CALL_MEMBER_FN(*this, function)(*it, *it);
      }
    }
  }
}