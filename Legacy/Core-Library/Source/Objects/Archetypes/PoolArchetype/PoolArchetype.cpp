/* ======================================================================== */
/*!
 * \file            PoolArchetype.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Used to initialize an object pool. Provides starting values of pool
   components using its pool component map. Only provides names of object 
   components, as object components are initialized later with an
   ObjectArchetype.
 */
/* ======================================================================== */

#include "stdafx.h"
#include "PoolArchetype.hpp"

namespace Barrage
{
  PoolArchetype::PoolArchetype() :
    poolComponents_(),
    objectComponents_()
  {
  }

  PoolArchetype::~PoolArchetype()
  {
    for (auto it = poolComponents_.begin(); it != poolComponents_.end(); ++it)
    {
      delete it->second;
    }
  }
}