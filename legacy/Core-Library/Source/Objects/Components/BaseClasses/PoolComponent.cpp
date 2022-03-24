/* ======================================================================== */
/*!
 * \file            PoolComponent.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 

 */
/* ======================================================================== */

#include "stdafx.h"
#include "PoolComponent.hpp"

namespace Barrage
{ 
  Component::Type PoolComponent::GetType()
  {
    return Component::Type::POOL_COMPONENT;
  }
}