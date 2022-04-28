/* ======================================================================== */
/*!
 * \file            PoolArchetype.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Used to initialize an object pool. Provides starting values of shared
   components using its shared component map. Only provides names of component 
   arrays, as components in component arrays are initialized later with an
   ObjectArchetype.
 */
/* ======================================================================== */

#include "stdafx.h"
#include "PoolArchetype.hpp"

namespace Barrage
{
  PoolArchetype::PoolArchetype() :
    sharedComponents_(),
    componentArrayNames_(),
    tags_()
  {
  }

  PoolArchetype::~PoolArchetype()
  {
    for (auto it = sharedComponents_.begin(); it != sharedComponents_.end(); ++it)
    {
      delete it->second;
    }
  }
}