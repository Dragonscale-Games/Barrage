/* ======================================================================== */
/*!
 * \file            PoolType.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A pool type is a combination of component names and tags. If a pool's
   components and tags match the pool type, it's considered to be that type.
*/
/* ======================================================================== */

#include "stdafx.h"
#include "PoolType.hpp"

namespace Barrage
{
  PoolType::PoolType() :
    tags_(),
    componentNames_()
  {
  }

  void PoolType::AddTag(const std::string& tag)
  {
    tags_.push_back(tag);
  }

  void PoolType::AddComponentName(const std::string& name)
  {
    componentNames_.push_back(name);
  }

  bool PoolType::MatchesPool(Pool* pool)
  {
    for (const auto& component : componentNames_)
    {
      if (!pool->HasComponentArray(component))
      {
        if (!pool->HasSharedComponent(component))
        {
          // if it doesn't exist in either list, the pool doesn't have the required component
          return false;
        }
      }
    }

    for (const auto& tag : tags_)
    {
      if (!pool->HasTag(tag))
      {
        return false;
      }
    }

    // if we made it here, the pool matches the pool type
    return true;
  }
}