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
  GenericComponent::GenericComponent(std::nullptr_t) :
    ptr_(nullptr)
  {
  }
  
  GenericComponent::GenericComponent(std::shared_ptr<Component> ptr) :
    ptr_(ptr)
  {
  }

  GenericComponent::GenericComponent(const GenericComponent& other) :
    ptr_(other ? other->Clone() : nullptr)
  {
  }

  GenericComponent& GenericComponent::operator=(const GenericComponent& other)
  {
    ptr_ = other ? other->Clone() : nullptr;

    return *this;
  }

  GenericComponent::GenericComponent(GenericComponent&& other) noexcept :
    ptr_(std::move(other.ptr_))
  {
  }

  GenericComponent& GenericComponent::operator=(GenericComponent&& other) noexcept
  {
    if (this != &other) // Prevent self-assignment
    {
      ptr_ = std::move(other.ptr_);
    }

    return *this;
  }

  Component* GenericComponent::operator->() const 
  {
    return ptr_.operator->();
  }

  Component& GenericComponent::operator*() const 
  {
    return *ptr_;
  }

  GenericComponent::operator bool() const noexcept
  {
    return static_cast<bool>(ptr_);
  }
}