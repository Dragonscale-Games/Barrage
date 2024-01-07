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
  GenericComponentArray::GenericComponentArray(std::nullptr_t) :
    ptr_(nullptr)
  {
  }

  GenericComponentArray::GenericComponentArray(std::shared_ptr<ComponentArray> ptr) :
    ptr_(ptr)
  {
  }

  GenericComponentArray::GenericComponentArray(const GenericComponentArray& other) :
    ptr_(other ? other->Clone() : nullptr)
  {
  }

  GenericComponentArray& GenericComponentArray::operator=(const GenericComponentArray& other)
  {
    ptr_ = other ? other->Clone() : nullptr;

    return *this;
  }

  GenericComponentArray::GenericComponentArray(GenericComponentArray&& other) noexcept :
    ptr_(std::move(other.ptr_))
  {
  }

  GenericComponentArray& GenericComponentArray::operator=(GenericComponentArray&& other) noexcept
  {
    if (this != &other) // Prevent self-assignment
    {
      ptr_ = std::move(other.ptr_);
    }

    return *this;
  }

  ComponentArray* GenericComponentArray::operator->() const
  {
    return ptr_.operator->();
  }

  ComponentArray& GenericComponentArray::operator*() const
  {
    return *ptr_;
  }

  GenericComponentArray::operator bool() const noexcept
  {
    return static_cast<bool>(ptr_);
  }
}