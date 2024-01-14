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
  
  ComponentArrayDeepPtr::ComponentArrayDeepPtr(std::nullptr_t) :
    ptr_(nullptr)
  {
  }

  ComponentArrayDeepPtr::ComponentArrayDeepPtr(std::shared_ptr<ComponentArray> ptr) :
    ptr_(ptr)
  {
  }

  ComponentArrayDeepPtr::ComponentArrayDeepPtr(const ComponentArrayDeepPtr& other) :
    ptr_(other ? other->Clone() : nullptr)
  {
  }

  ComponentArrayDeepPtr& ComponentArrayDeepPtr::operator=(const ComponentArrayDeepPtr& other)
  {
    ptr_ = other ? other->Clone() : nullptr;

    return *this;
  }

  ComponentArrayDeepPtr::ComponentArrayDeepPtr(ComponentArrayDeepPtr&& other) noexcept :
    ptr_(std::move(other.ptr_))
  {
  }

  ComponentArrayDeepPtr& ComponentArrayDeepPtr::operator=(ComponentArrayDeepPtr&& other) noexcept
  {
    if (this != &other) // Prevent self-assignment
    {
      ptr_ = std::move(other.ptr_);
    }

    return *this;
  }

  ComponentArray* ComponentArrayDeepPtr::operator->() const
  {
    return ptr_.operator->();
  }

  ComponentArray& ComponentArrayDeepPtr::operator*() const
  {
    return *ptr_;
  }

  ComponentArrayDeepPtr::operator bool() const noexcept
  {
    return static_cast<bool>(ptr_);
  }
}