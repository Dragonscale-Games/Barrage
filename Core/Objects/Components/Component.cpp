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
  ComponentPtr::ComponentPtr(std::nullptr_t) :
    ptr_(nullptr)
  {
  }
  
  ComponentPtr::ComponentPtr(std::shared_ptr<Component> ptr) :
    ptr_(ptr)
  {
  }

  ComponentPtr::ComponentPtr(const ComponentPtr& other) :
    ptr_(other->Clone())
  {
  }

  ComponentPtr& ComponentPtr::operator=(const ComponentPtr& other)
  {
    ptr_ = other->Clone();

    return *this;
  }

  ComponentPtr::ComponentPtr(ComponentPtr&& other) noexcept :
    ptr_(std::move(other.ptr_))
  {
  }

  ComponentPtr& ComponentPtr::operator=(ComponentPtr&& other) noexcept
  {
    if (this != &other) // Prevent self-assignment
    {
      ptr_ = std::move(other.ptr_);
    }

    return *this;
  }

  Component* ComponentPtr::operator->() const 
  {
    return ptr_.operator->();
  }

  Component& ComponentPtr::operator*() const 
  {
    return *ptr_;
  }

  ComponentPtr::operator bool() const noexcept
  {
    return static_cast<bool>(ptr_);
  }
}