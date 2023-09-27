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
  ComponentArrayPtr::ComponentArrayPtr(std::nullptr_t) :
    ptr_(nullptr)
  {
  }

  ComponentArrayPtr::ComponentArrayPtr(std::shared_ptr<ComponentArray> ptr) :
    ptr_(ptr)
  {
  }

  ComponentArrayPtr::ComponentArrayPtr(const ComponentArrayPtr& other) :
    ptr_(other->Clone())
  {
  }

  ComponentArrayPtr& ComponentArrayPtr::operator=(const ComponentArrayPtr& other)
  {
    ptr_ = other->Clone();

    return *this;
  }

  ComponentArrayPtr::ComponentArrayPtr(ComponentArrayPtr&& other) noexcept :
    ptr_(std::move(other.ptr_))
  {
  }

  ComponentArrayPtr& ComponentArrayPtr::operator=(ComponentArrayPtr&& other) noexcept
  {
    if (this != &other) // Prevent self-assignment
    {
      ptr_ = std::move(other.ptr_);
    }

    return *this;
  }

  ComponentArray* ComponentArrayPtr::operator->() const
  {
    return ptr_.operator->();
  }

  ComponentArray& ComponentArrayPtr::operator*() const
  {
    return *ptr_;
  }

  ComponentArrayPtr::operator bool() const noexcept
  {
    return static_cast<bool>(ptr_);
  }
}