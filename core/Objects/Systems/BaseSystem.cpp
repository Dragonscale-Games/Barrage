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
    systemComponents_(),
    pools_()
  {
  }

  void System::Subscribe(Pool* pool)
  {
    if (PoolMatchesSystem(pool))
    {
      pools_.insert(std::pair<unsigned, Pool*>(0, pool));
    }
  }

  void System::Unsubscribe(Pool* pool)
  {
    for (auto it = pools_.begin(); it != pools_.end(); ++it)
    {
      if (it->second == pool)
      {
        pools_.erase(it);
        return;
      }
    }
  }

  void System::Update()
  {
    for (auto it = pools_.begin(); it != pools_.end(); ++it)
    {
      UpdatePool(it->second);
    }
  }

  void System::UpdatePool(Pool* pool)
  {
    UNREFERENCED(pool);
  }

  bool System::PoolMatchesSystem(Pool* pool)
  {
    // for each required component...
    for (auto component : systemComponents_)
    {
      // check if it's in the object component list
      if (pool->objectComponents_.count(component) == 0)
      {
        // if it wasn't, check if it's in the pool component list
        if (pool->poolComponents_.count(component) == 0)
        {
          // if it doesn't exist in either list, the pool doesn't have the required component
          return false;
        }
      }
    }

    // if we made it here, the pool contains all required components
    return true;
  }
}