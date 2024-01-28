/* ======================================================================== */
/*!
 * \file            DestructionSystem.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Handles destruction for all destructible objects. All destroyed objects
   are lazy deleted, then all remaining active objects are sorted to the
   front of the pool and the active object count is updated.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "DestructionSystem.hpp"
#include "ComponentArrays/Destructible/DestructibleArray.hpp"
#include "Components/Spawner/Spawner.hpp"
#include "Components/Behavior/Behavior.hpp"

namespace Barrage
{
  static const std::string DESTRUCTIBLE_POOLS("Destructible Pools");
  
  DestructionSystem::DestructionSystem() :
    System()
  {
    PoolType destructible_type;
    destructible_type.AddComponentArray("Destructible");
    poolTypes_[DESTRUCTIBLE_POOLS] = destructible_type;
  }
  
  void DestructionSystem::Update()
  {
    UpdatePoolGroup(DESTRUCTIBLE_POOLS, DestroyObjects);
  }

  void DestructionSystem::DestroyObjects(Space& space, Pool& pool)
  {
    DestructibleArray& destructibleArray = pool.GetComponentArray<Destructible>("Destructible");
    Destructible* destructiblesRaw = destructibleArray.GetRaw();
    unsigned numActiveObjects = pool.ActiveObjectCount();
    unsigned deadBeginIndex = GetFirstDeadObjectIndex(destructibleArray, numActiveObjects);

    // if no objects were destroyed, early out
    if (deadBeginIndex >= numActiveObjects)
      return;

    for (auto it = pool.components_.begin(); it != pool.components_.end(); ++it)
    {
      it->second->HandleDestructions(destructiblesRaw, deadBeginIndex, numActiveObjects);
    }

    for (auto it = pool.componentArrays_.begin(); it != pool.componentArrays_.end(); ++it)
    {
      // we'll operate on the destructible array last; after the loop finishes
      if (it->first == "Destructible")
        continue;

      it->second->HandleDestructions(destructiblesRaw, deadBeginIndex, numActiveObjects);
    }

    // operate on the destructibles array last and update the number of alive objects in the pool
    pool.numActiveObjects_ = destructibleArray.HandleDestructions(destructibleArray.GetRaw(), deadBeginIndex, numActiveObjects);
  }

  unsigned DestructionSystem::GetFirstDeadObjectIndex(DestructibleArray& destructiblesArray, unsigned numElements)
  {
    unsigned index = 0;

    while (index < numElements)
    {
      if (destructiblesArray.Data(index).destroyed_ == true)
      {
        break;
      }
        
      ++index;
    }

    return index;
  }
}