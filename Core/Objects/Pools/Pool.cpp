/* ======================================================================== */
/*!
 * \file            Pool.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   An object pool is a block of memory that can hold a prespecified number
   of objects with a specific combination of components.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "Pool.hpp"

namespace Barrage
{
  Pool::Pool(unsigned capacity) :
    tags_(),
    componentArrays_(),
    sharedComponents_(),
    size_(0),
    capacity_(capacity)
  {
  }

  Pool::~Pool()
  {
    // deallocate component arrays
    for (auto it = componentArrays_.begin(); it != componentArrays_.end(); ++it)
    {
      delete it->second;
    }

    // deallocate shared components
    for (auto it = sharedComponents_.begin(); it != sharedComponents_.end(); ++it)
    {
      delete it->second;
    }
  }

  bool Pool::HasTag(const std::string& tag) const
  {
    return tags_.count(tag);
  }
}