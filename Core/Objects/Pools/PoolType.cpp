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
    // for each of the pool type's required components...
    for (const auto& component : componentNames_)
    {
      // check if it's in the pool's component array list
      if (pool->componentArrays_.count(component) == 0)
      {
        // if it wasn't, check if it's in the pool's shared component list
        if (pool->sharedComponents_.count(component) == 0)
        {
          // if it doesn't exist in either list, the pool doesn't have the required component
          return false;
        }
      }
    }

    // for each of the pool type's required tags...
    for (const auto& tag : tags_)
    {
      // check if it's in the pool's tag list
      if (pool->tags_.count(tag) == 0)
      {
        // if it doesn't exist, the pool doesn't have the required tag
        return false;
      }
    }

    // if we made it here, the pool matches the pool type
    return true;
  }
}