/* ======================================================================== */
/*!
 * \file            System.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base system class that all systems should inherit from.

   An system is a collection of related functions that perform operations
   on game objects. For instance, a movement system might contain all
   functions that change an object's position.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "System.hpp"

namespace Barrage
{
  System::System() :
    poolTypes_(),
    poolGroups_()
  {
  }

  void System::Subscribe(Pool* pool)
  {
    for (auto it = poolTypes_.begin(); it != poolTypes_.end(); ++it)
    {
      PoolType& pool_type = it->second;

      if (pool_type.MatchesPool(pool))
      {
        poolGroups_[it->first].push_back(pool);
      }
    }
  }

  void System::Unsubscribe(Pool* pool)
  {
    for (auto it = poolGroups_.begin(); it != poolGroups_.end(); ++it)
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
    // intentionally empty - specialized in subclasses
  }

  void System::UpdatePoolGroup(const std::string& group, PoolUpdateFunction function)
  {
    if (poolGroups_.find(group) != poolGroups_.end())
    {
      std::vector<Pool*>& pool_group = poolGroups_[group];

      for (auto it = pool_group.begin(); it != pool_group.end(); ++it)
      {
        function(**it);
      }
    }
  }

  void System::UpdatePoolGroup(const std::string& group, PoolUpdateMemberFunction function)
  {
    std::vector<Pool*>& pool_group = poolGroups_[group];

    for (auto it = pool_group.begin(); it != pool_group.end(); ++it)
    {
      CALL_MEMBER_FN(*this, function)(**it);
    }
  }

  void System::UpdateInteraction(const std::string& group1, const std::string& group2, InteractionFunction function)
  {
    std::vector<Pool*>& pool_group_1 = poolGroups_[group1];
    std::vector<Pool*>& pool_group_2 = poolGroups_[group2];

    for (auto it = pool_group_1.begin(); it != pool_group_1.end(); ++it)
    {
      for (auto jt = pool_group_2.begin(); jt != pool_group_2.end(); ++jt)
      {
        function(**it, **jt);
      }
    }
  }

  void System::UpdateInteraction(const std::string& group1, const std::string& group2, InteractionMemberFunction function)
  {
    std::vector<Pool*>& pool_group_1 = poolGroups_[group1];
    std::vector<Pool*>& pool_group_2 = poolGroups_[group2];

    for (auto it = pool_group_1.begin(); it != pool_group_1.end(); ++it)
    {
      for (auto jt = pool_group_2.begin(); jt != pool_group_2.end(); ++jt)
      {
        CALL_MEMBER_FN(*this, function)(**it, **jt);
      }
    }
  }
}