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
    componentNames_(),
    componentArrayNames_()
  {
  }

  void PoolType::AddTag(const std::string_view& tag)
  {
    tags_.push_back(tag);
  }

  void PoolType::AddComponent(const std::string_view& name)
  {
    componentNames_.push_back(name);
  }

  void PoolType::AddComponentArray(const std::string_view& name)
  {
    componentArrayNames_.push_back(name);
  }

  bool PoolType::MatchesPool(Pool* pool)
  {
    for (const auto& component : componentNames_)
    {
      if (!pool->HasComponent(component))
      {
        return false;
      }
    }
    
    for (const auto& componentArray : componentArrayNames_)
    {
      if (!pool->HasComponentArray(componentArray))
      {
        return false;
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