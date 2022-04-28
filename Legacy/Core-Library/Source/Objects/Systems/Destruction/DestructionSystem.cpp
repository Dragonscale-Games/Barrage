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
  DestructionSystem::DestructionSystem() :
    System()
  {
    systemComponents_.push_back("Destructible");
  }
  
  void DestructionSystem::UpdatePool(Pool* pool)
  {
    PerComponentDestructionAlgorithm(pool);
  }

  void DestructionSystem::PerObjectDestructionAlgorithm(Pool* pool)
  {
    Destructible* destructibles = dynamic_cast<Destructible*>(pool->objectComponents_.at("Destructible"));

    /*
     *  Objectives:
     *  1. Shift all alive objects to be densely packed at the beginning of the object array.
     *  2. Make this change in-place, using the original object array (and update the size).
     *  3. Preserve the relative order of the alive objects.
     */

    // index that will be one past the end of our alive objects
    unsigned alive_end_index = 0;

    // starting at the beginning of the object array, find the index of the first destroyed object (if one exists)
    while (alive_end_index < pool->activeObjects_)
    {
      if (destructibles->data_[alive_end_index].destroyed_ == true)
        break;

      ++alive_end_index;
    }

    // this keeps track of the next alive object that isn't packed at the beginning of our object array (if one exists)
    // we'll start searching for this object at the first index where it is possible to have such an object
    unsigned next_alive_index = alive_end_index + 1;

    // make sure we're only looking for additional alive objects within the original bounds of the array
    while (next_alive_index < pool->activeObjects_)
    {
      // if an alive object is found that needs to be packed...
      if (destructibles->data_[next_alive_index].destroyed_ == false)
      {
        // copy the object to the end of the packed subarray
        CopyObject(pool, next_alive_index, alive_end_index);

        // update the packed subarray's end index
        ++alive_end_index;
      }

      ++next_alive_index;
    }

    // update the size of the newly packed object array
    pool->activeObjects_ = alive_end_index;
  }

  void DestructionSystem::PerComponentDestructionAlgorithm(Pool* pool)
  {
    Destructible* destructibles = dynamic_cast<Destructible*>(pool->objectComponents_.at("Destructible"));

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
    while (initial_alive_end_index < pool->activeObjects_)
    {
      if (destructibles->data_[initial_alive_end_index].destroyed_ == true)
        break;

      ++initial_alive_end_index;
    }

    // if no objects were destroyed, early out
    if (initial_alive_end_index >= pool->activeObjects_)
      return;

    // in each component array, shift the components from alive objects to the beginning of the array
    for (auto it = pool->objectComponents_.begin(); it != pool->objectComponents_.end(); ++it)
    {
      // we'll operate on the destructible array last; after the loop finishes
      if (it->first == "Destructible")
        continue;
      
      unsigned alive_end_index = initial_alive_end_index;
      unsigned next_alive_index = alive_end_index + 1;

      ObjectComponent* component = it->second;

      while (next_alive_index < pool->activeObjects_)
      {
        if (destructibles->data_[next_alive_index].destroyed_ == false)
        {
          component->CopyToThis(*component, next_alive_index, alive_end_index);

          ++alive_end_index;
        }

        ++next_alive_index;
      }
    }

    // operate on the destructibles array last, after all other components
    unsigned alive_end_index = initial_alive_end_index;
    unsigned next_alive_index = alive_end_index + 1;

    while (next_alive_index < pool->activeObjects_)
    {
      if (destructibles->data_[next_alive_index].destroyed_ == false)
      {
        destructibles->CopyToThis(*destructibles, next_alive_index, alive_end_index);

        ++alive_end_index;
      }

      ++next_alive_index;
    }

    // update the size of the newly packed object array
    pool->activeObjects_ = alive_end_index;
  }

  void DestructionSystem::CopyObject(Pool* pool, unsigned sourceIndex, unsigned recipientIndex) const
  {
    for (auto it = pool->objectComponents_.begin(); it != pool->objectComponents_.end(); ++it)
    {
      ObjectComponent* component = it->second;

      component->CopyToThis(*component, sourceIndex, recipientIndex);
    }
  }
}