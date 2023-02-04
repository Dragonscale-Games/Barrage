/* ======================================================================== */
/*!
 * \file            ComponentAllocator.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Interface for allocating any type of component via its name.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "ComponentAllocator.hpp"

namespace Barrage
{
  ComponentAllocator::ComponentAllocator() :
    componentArrayAllocMap_(),
    sharedComponentAllocMap_(),
    componentArrayNames_(),
    sharedComponentNames_()
  {
  }

  ComponentArray* ComponentAllocator::AllocateComponentArray(const std::string_view& name, unsigned capacity) const
  {
    if (componentArrayAllocMap_.find(name) == componentArrayAllocMap_.end())
    {
      return nullptr;
    }
    else
    {
      return CALL_MEMBER_FN(*this, componentArrayAllocMap_.at(name))(capacity);
    }
  }

  SharedComponent* ComponentAllocator::AllocateSharedComponent(const std::string_view& name, SharedComponent* initializer) const
  {
    if (sharedComponentAllocMap_.find(name) == sharedComponentAllocMap_.end())
    {
      return nullptr;
    }
    else
    {
      return CALL_MEMBER_FN(*this, sharedComponentAllocMap_.at(name))(initializer);
    }
  }

  std::vector<std::string_view> ComponentAllocator::GetComponentArrayNames()
  {
    return componentArrayNames_;
  }

  std::vector<std::string_view> ComponentAllocator::GetSharedComponentNames()
  {
    return sharedComponentNames_;
  }
}