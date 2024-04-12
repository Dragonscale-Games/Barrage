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
   For instance, each object may need its own position component.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "ComponentArray.hpp"

namespace Barrage
{
  ComponentArray::ComponentArray(unsigned capacity) :
    capacity_(capacity)
  {
  }

  unsigned ComponentArray::GetCapacity()
  {
    return capacity_;
  }
}