/* ======================================================================== */
/*!
 * \file            Pool.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   An object pool is a block of memory that can hold a prespecified number
   of objects with a specific combination of components.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "Pool.hpp"
#include "Spaces/Space.hpp"

namespace Barrage
{
  Pool::Pool(unsigned capacity, Space& space) :
    tags_(),
    componentArrays_(),
    sharedComponents_(),
    numActiveObjects_(0),
    numQueuedObjects_(0),
    capacity_(capacity),
    space_(space)
  {
  }

  Pool::~Pool()
  {
    // deallocate component arrays
    for (auto it = componentArrays_.begin(); it != componentArrays_.end(); ++it)
    {
      delete it->second;
    }

    // deallocate shared components
    for (auto it = sharedComponents_.begin(); it != sharedComponents_.end(); ++it)
    {
      delete it->second;
    }
  }

  bool Pool::HasTag(const std::string_view& tag) const
  {
    return tags_.count(tag);
  }

  bool Pool::HasComponentArray(const std::string_view& componentArrayName)
  {
    return componentArrays_.count(componentArrayName);
  }

  bool Pool::HasSharedComponent(const std::string_view& sharedComponentName)
  {
    return sharedComponents_.count(sharedComponentName);
  }

  unsigned Pool::GetAvailableSlots() const
  {
    return capacity_ - numActiveObjects_ - numQueuedObjects_;
  }
}