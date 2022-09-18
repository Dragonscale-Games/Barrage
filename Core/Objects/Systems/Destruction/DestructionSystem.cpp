/* ======================================================================== */
/*!
 * \file            DestructionSystem.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 
 */
/* ======================================================================== */

#include "stdafx.h"
#include "DestructionSystem.hpp"

namespace Barrage
{
  static const unsigned BASIC_DESTRUCTIBLE_POOLS = 0;
  static const unsigned HANDLE_POOLS = 1;
  
  DestructionSystem::DestructionSystem() :
    System()
  {
    PoolType destructible_type;
    destructible_type.AddComponentName("DestructibleArray");
    poolTypes_[BASIC_DESTRUCTIBLE_POOLS] = destructible_type;

    PoolType handle_type;
    handle_type.AddComponentName("DestructibleArray");
    handle_type.AddComponentName("HandleIndexArray");
    handle_type.AddComponentName("HandleDirectory");
    poolTypes_[HANDLE_POOLS] = handle_type;
  }
  
  void DestructionSystem::Update()
  {
    UpdatePoolGroup(HANDLE_POOLS, UpdateDeadHandles);
    UpdatePoolGroup(BASIC_DESTRUCTIBLE_POOLS, DestroyObjects);
    UpdatePoolGroup(HANDLE_POOLS, UpdateAliveHandles);
  }

  void DestructionSystem::UpdateDeadHandles(Pool* pool)
  {
    DestructibleArray& destructible_array = *pool->GetComponentArray<DestructibleArray>("DestructibleArray");
    HandleIndexArray& handle_index_array = *pool->GetComponentArray<HandleIndexArray>("HandleIndexArray");
    HandleDirectory& handle_directory = *pool->GetSharedComponent<HandleDirectory>("HandleDirectory");

    unsigned num_objects = pool->size_;

    for (unsigned i = 0; i < num_objects; ++i)
    {
      if (destructible_array[i].destroyed_)
      {
        unsigned handle_index = handle_index_array[i].index_;

        handle_directory.FreeHandle(handle_index);
      }
    }
  }

  void DestructionSystem::UpdateAliveHandles(Pool* pool)
  {
    HandleIndexArray& handle_index_array = *pool->GetComponentArray<HandleIndexArray>("HandleIndexArray");
    HandleDirectory& handle_directory = *pool->GetSharedComponent<HandleDirectory>("HandleDirectory");

    unsigned num_objects = pool->size_;

    for (unsigned i = 0; i < num_objects; ++i)
    {
      unsigned handle_index = handle_index_array[i].index_;
      Handle& handle = handle_directory.GetHandle(handle_index);

      handle.poolIndex_ = i;
    }
  }

  void DestructionSystem::DestroyObjects(Pool* pool)
  {
    DestructibleArray& destructible_array = *pool->GetComponentArray<DestructibleArray>("DestructibleArray");

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
    while (initial_alive_end_index < pool->size_)
    {
      if (destructible_array[initial_alive_end_index].destroyed_ == true)
        break;

      ++initial_alive_end_index;
    }

    // if no objects were destroyed, early out
    if (initial_alive_end_index >= pool->size_)
      return;

    // in each component array, shift the components from alive objects to the beginning of the array
    for (auto it = pool->componentArrays_.begin(); it != pool->componentArrays_.end(); ++it)
    {
      // we'll operate on the destructible array last; after the loop finishes
      if (it->first == "DestructibleArray")
        continue;

      unsigned alive_end_index = initial_alive_end_index;
      unsigned next_alive_index = alive_end_index + 1;

      ComponentArray* component_array = it->second;

      while (next_alive_index < pool->size_)
      {
        if (destructible_array[next_alive_index].destroyed_ == false)
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

    while (next_alive_index < pool->size_)
    {
      if (destructible_array[next_alive_index].destroyed_ == false)
      {
        destructible_array.CopyToThis(destructible_array, next_alive_index, alive_end_index);

        ++alive_end_index;
      }

      ++next_alive_index;
    }

    // update the size of the newly packed object array
    pool->size_ = alive_end_index;
  }
}