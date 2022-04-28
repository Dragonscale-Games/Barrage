/* ======================================================================== */
/*!
 * \file            ObjectArchetype.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Used to initialize new objects by copying the values in its component map.
 */
/* ======================================================================== */

#include "stdafx.h"
#include "ObjectArchetype.hpp"

namespace Barrage
{
  ObjectArchetype::ObjectArchetype() :
    objectComponents_()
  {
  }

  ObjectArchetype::~ObjectArchetype()
  {
    for (auto it = objectComponents_.begin(); it != objectComponents_.end(); ++it)
    {
      delete it->second;
    }
  }
}