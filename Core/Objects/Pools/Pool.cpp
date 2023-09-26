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
  Pool::Pool(const PoolArchetype& archetype) :
    components_(),
    componentArrays_(),
    tags_(),
    numActiveObjects_(0),
    numQueuedObjects_(0),
    capacity_(archetype.GetCapacity()),
    name_(archetype.GetName())
  {
  }
}