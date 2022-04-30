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
    size_t num_pool_types = poolTypes_.size();

    for (int i = 0; i < num_pool_types; ++i)
    {
      if (poolTypes_[i].MatchesPool(pool))
      {
        pools_.insert(std::pair<unsigned, Pool*>(static_cast<unsigned>(i), pool));
        return;
      }
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
}