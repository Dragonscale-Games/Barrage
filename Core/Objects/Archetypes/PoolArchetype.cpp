/* ======================================================================== */
/*!
 * \file            PoolArchetype.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Used to initialize an object pool. Provides starting values of components
   on the pool. Only provides names of component arrays, as components in
   component arrays are initialized later with an ObjectArchetype.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "PoolArchetype.hpp"
#include "Objects/Components/ComponentFactory.hpp"

namespace Barrage
{
  PoolArchetype::PoolArchetype(const std::string& name, unsigned capacity) :
    name_(name),
    capacity_(capacity),
    components_(),
    componentArrayNames_(),
    tags_(),
    startingObjects_(),
    spawnArchetypes_()
  {
  }

  const std::string& PoolArchetype::GetName() const
  {
    return name_;
  }
}