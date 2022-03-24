/* ======================================================================== */
/*!
 * \file            ComponentAllocator.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 

 */
/* ======================================================================== */

#include "stdafx.h"
#include "ComponentAllocator.hpp"

namespace Barrage
{
  ComponentAllocator::ComponentAllocator() :
    objectComponentAllocMap_(),
    poolComponentAllocMap_(),
    objectComponentNames_(),
    poolComponentNames_()
  {
  }

  ObjectComponent* ComponentAllocator::AllocateObjectComponentArray(const std::string& name, unsigned capacity) const
  {
    if (objectComponentAllocMap_.find(name) == objectComponentAllocMap_.end())
    {
      return nullptr;
    }
    else
    {
      return CALL_MEMBER_FN(*this, objectComponentAllocMap_.at(name))(capacity);
    }
  }

  PoolComponent* ComponentAllocator::AllocatePoolComponent(const std::string& name, PoolComponent* initializer) const
  {
    if (poolComponentAllocMap_.find(name) == poolComponentAllocMap_.end())
    {
      return nullptr;
    }
    else
    {
      return CALL_MEMBER_FN(*this, poolComponentAllocMap_.at(name))(initializer);
    }
  }

  ObjectComponentList ComponentAllocator::GetObjectComponentNames()
  {
    return objectComponentNames_;
  }

  PoolComponentList ComponentAllocator::GetPoolComponentNames()
  {
    return poolComponentNames_;
  }
}