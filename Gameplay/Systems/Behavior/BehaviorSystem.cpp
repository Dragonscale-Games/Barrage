/* ======================================================================== */
/*!
 * \file            BehaviorSystem.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here>
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "BehaviorSystem.hpp"

#include "Components/Behavior/Behavior.hpp"

namespace Barrage
{
  static const std::string BEHAVIOR_POOLS("Behavior Pools");

  BehaviorSystem::BehaviorSystem() :
    System()
  {
    PoolType behavior_type;
    behavior_type.AddComponent("BehaviorTree");
    poolTypes_[BEHAVIOR_POOLS] = behavior_type;
  }

  void BehaviorSystem::Subscribe(Space& space, Pool* pool)
  {
    for (auto it = poolTypes_.begin(); it != poolTypes_.end(); ++it)
    {
      PoolType& pool_type = it->second;

      if (pool_type.MatchesPool(pool))
      {
        BehaviorTree& behaviorTree = pool->GetComponent<BehaviorTree>("BehaviorTree").Data();

        behaviorTree.SetCapacity(pool->GetCapacity());
        behaviorTree.BuildTree();

        poolGroups_[it->first].push_back(pool);
      }
    }
  }

  void BehaviorSystem::Update()
  {
    UpdatePoolGroup(BEHAVIOR_POOLS, ExecuteBehaviorTree);
  }

  void BehaviorSystem::ExecuteBehaviorTree(Space& space, Pool& pool)
  {
    BehaviorTree& behaviorTree = pool.GetComponent<BehaviorTree>("BehaviorTree").Data();
    
    behaviorTree.Execute(space, pool);
  }
}