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
  
  DestructionSystem::DestructionSystem() :
    System()
  {
    PoolType destructible_type;
    destructible_type.AddComponentName("DestructibleArray");
    poolTypes_[BASIC_DESTRUCTIBLE_POOLS] = destructible_type;
  }
  
  void DestructionSystem::Update()
  {
    UpdatePoolGroup(BASIC_DESTRUCTIBLE_POOLS, UpdateBasicDestructibles);
  }

  void DestructionSystem::UpdateBasicDestructibles(Pool* pool)
  {
    /* Only use one of these algorithms - profile and see which is faster */ 

    // PerObjectDestructionAlgorithm(pool);
    PerComponentDestructionAlgorithm(pool);
  }

  void DestructionSystem::PerObjectDestructionAlgorithm(Pool* pool)
  {
    DestructibleArray& destructible_array = *pool->GetComponentArray<DestructibleArray>("DestructibleArray");

    /*
     *  Objectives:
     *  1. Shift all alive objects to be densely packed at the beginning of the object array.
     *  2. Make this change in-place, using the original object array (and update the size).
     *  3. Preserve the relative order of the alive objects.
     */

    // index that will be one past the end of our alive objects
    unsigned alive_end_index = 0;

    // starting at the beginning of the object array, find the index of the first destroyed object (if one exists)
    while (alive_end_index < pool->size_)
    {
      if (destructible_array[alive_end_index].destroyed_ == true)
        break;

      ++alive_end_index;
    }

    // this keeps track of the next alive object that isn't packed at the beginning of our object array (if one exists)
    // we'll start searching for this object at the first index where it is possible to have such an object
    unsigned next_alive_index = alive_end_index + 1;

    // make sure we're only looking for additional alive objects within the original bounds of the array
    while (next_alive_index < pool->size_)
    {
      // if an alive object is found that needs to be packed...
      if (destructible_array[next_alive_index].destroyed_ == false)
      {
        // copy the object to the end of the packed subarray
        CopyObject(pool, next_alive_index, alive_end_index);

        // update the packed subarray's end index
        ++alive_end_index;
      }

      ++next_alive_index;
    }

    // update the size of the newly packed object array
    pool->size_ = alive_end_index;
  }

  void DestructionSystem::PerComponentDestructionAlgorithm(Pool* pool)
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

  void DestructionSystem::CopyObject(Pool* pool, unsigned sourceIndex, unsigned recipientIndex)
  {
    for (auto it = pool->componentArrays_.begin(); it != pool->componentArrays_.end(); ++it)
    {
      ComponentArray* component_array = it->second;

      component_array->CopyToThis(*component_array, sourceIndex, recipientIndex);
    }
  }
}