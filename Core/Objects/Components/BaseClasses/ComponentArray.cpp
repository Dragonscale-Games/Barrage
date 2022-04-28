/* ======================================================================== */
/*!
 * \file            ComponentArray.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base component array class that all component arrays should inherit from.
   Component arrays are used when each object in a pool needs its own copy
   of a component.
 */
/* ======================================================================== */

#include "stdafx.h"
#include "ComponentArray.hpp"

namespace Barrage
{
  Component::Type ComponentArray::GetType()
  {
    return Component::Type::ARRAY;
  }
}