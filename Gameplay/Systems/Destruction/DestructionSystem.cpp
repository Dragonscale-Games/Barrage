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
#include "ComponentArrays/DestructibleArray.hpp"

namespace Barrage
{
  static const unsigned BASIC_DESTRUCTIBLE_POOLS = 0;
  static const unsigned DIRECTORY_POOLS = 1;
  
  DestructionSystem::DestructionSystem() :
    System()
  {
    PoolType destructible_type;
    destructible_type.AddComponentArray("Destructible");
    poolTypes_["Basic Destructible Pools"] = destructible_type;
  }
  
  void DestructionSystem::Update()
  {
    UpdatePoolGroup("Basic Destructible Pools", DestroyObjects);
  }

  void DestructionSystem::DestroyObjects(Pool* pool)
  {
    DestructibleArray& destructible_array = *pool->GetComponentArray<Destructible>("Destructible");

    /*
     *  Objectives:
     *  1. Shift all alive objects to be densely packed at the beginning of the object array.
     *  2. Make this change in-place, using the original object array (and update the size).
     *  3. Preserve the relative order of the alive objects.
     */

     // keep track of where the first dead object is, this will be reused as a starting place for each component array
    unsigned initial_alive_end_index = 0;

    // starting at the beginning of the original object array, find the index of the first destroyed object (if one exists) or one
    // past the end of the original object array
    while (initial_alive_end_index < pool->numActiveObjects_)
    {
      if (destructible_array.Data(initial_alive_end_index).destroyed_ == true)
        break;

      ++initial_alive_end_index;
    }

    // if no objects were destroyed, early out
    if (initial_alive_end_index >= pool->numActiveObjects_)
      return;

    // in each component array, shift the components from alive objects to the beginning of the array
    for (auto it = pool->componentArrays_.begin(); it != pool->componentArrays_.end(); ++it)
    {
      // we'll operate on the destructible array last; after the loop finishes
      if (it->first == "Destructible")
        continue;

      unsigned alive_end_index = initial_alive_end_index;
      unsigned next_alive_index = alive_end_index + 1;

      ComponentArray* component_array = it->second;

      while (next_alive_index < pool->numActiveObjects_)
      {
        if (destructible_array.Data(next_alive_index).destroyed_ == false)
        {
          component_array->CopyToThis(*component_array, next_alive_index, alive_end_index);

          ++alive_end_index;
        }

        ++next_alive_index;
      }
    }

    // operate on the destructibles array last, after all other components
    unsigned alive_end_index = initial_alive_end_index;
    unsigned next_alive_index = alive_end_index + 1;

    while (next_alive_index < pool->numActiveObjects_)
    {
      if (destructible_array.Data(next_alive_index).destroyed_ == false)
      {
        destructible_array.CopyToThis(destructible_array, next_alive_index, alive_end_index);

        ++alive_end_index;
      }

      ++next_alive_index;
    }

    // update the size of the newly packed object array
    pool->numActiveObjects_ = alive_end_index;
  }
}