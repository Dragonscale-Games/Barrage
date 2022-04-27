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
    objectComponents_(),
    poolComponents_(),
    activeObjects_(0),
    capacity_(capacity)
  {
  }

  Pool::~Pool()
  {
    // deallocate object component arrays
    for (auto it = objectComponents_.begin(); it != objectComponents_.end(); ++it)
    {
      delete it->second;
    }

    // deallocate pool components
    for (auto it = poolComponents_.begin(); it != poolComponents_.end(); ++it)
    {
      delete it->second;
    }
  }
}