/* ======================================================================== */
/*!
 * \file            SharedComponent.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base shared component class that all shared components should inherit from.
   A shared component is a component that all objects in a pool use.
   For instance, all objects in a pool may use the same sprite component.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "SharedComponent.hpp"

namespace Barrage
{ 
  Component::Type SharedComponent::GetType()
  {
    return Component::Type::SHARED;
  }
}