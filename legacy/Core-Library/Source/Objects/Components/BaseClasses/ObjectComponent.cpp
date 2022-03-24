/* ======================================================================== */
/*!
 * \file            ObjectComponent.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base object component class that all object components should inherit from.
   An object component is a component that is unique per object that contains
   it.
 */
/* ======================================================================== */

#include "stdafx.h"
#include "ObjectComponent.hpp"

namespace Barrage
{
  Component::Type ObjectComponent::GetType()
  {
    return Component::Type::OBJECT_COMPONENT;
  }
}