/* ======================================================================== */
/*!
 * \file            Component.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base component class that all components should inherit from.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "Component.hpp"

namespace Barrage
{
  ComponentDeepPtr::ComponentDeepPtr(std::nullptr_t) :
    ptr_(nullptr)
  {
  }
  
  ComponentDeepPtr::ComponentDeepPtr(std::shared_ptr<Component> ptr) :
    ptr_(ptr)
  {
  }

  ComponentDeepPtr::ComponentDeepPtr(const ComponentDeepPtr& other) :
    ptr_(other ? other->Clone() : nullptr)
  {
  }

  ComponentDeepPtr& ComponentDeepPtr::operator=(const ComponentDeepPtr& other)
  {
    ptr_ = other ? other->Clone() : nullptr;

    return *this;
  }

  ComponentDeepPtr::ComponentDeepPtr(ComponentDeepPtr&& other) noexcept :
    ptr_(std::move(other.ptr_))
  {
  }

  ComponentDeepPtr& ComponentDeepPtr::operator=(ComponentDeepPtr&& other) noexcept
  {
    if (this != &other) // Prevent self-assignment
    {
      ptr_ = std::move(other.ptr_);
    }

    return *this;
  }

  Component* ComponentDeepPtr::operator->() const 
  {
    return ptr_.operator->();
  }

  Component& ComponentDeepPtr::operator*() const 
  {
    return *ptr_;
  }

  ComponentDeepPtr::operator bool() const noexcept
  {
    return static_cast<bool>(ptr_);
  }
}