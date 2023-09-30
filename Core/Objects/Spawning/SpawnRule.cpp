/* ======================================================================== */
/*!
 * \file            SpawnRule.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A spawn rule modifies the initial values of a newly spawned object.
 */
 /* ======================================================================== */

#include "SpawnRule.hpp"
#include "stdafx.h"

namespace Barrage
{
  SpawnRule::SpawnRule(const std::string& name) : name_(name)
  {
  }

  const std::string& SpawnRule::GetName() const
  {
    return name_;
  }

  rttr::variant SpawnRule::GetRTTRValue()
  {
    return rttr::variant();
  }

  void SpawnRule::SetRTTRValue(const rttr::variant& value)
  {
    UNREFERENCED(value);
  }

  SpawnRuleWithArray::SpawnRuleWithArray(const std::string& name) : SpawnRule(name)
  {
  }

  void SpawnRuleWithArray::HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex)
  {
    UNREFERENCED(destructionArray);
    UNREFERENCED(writeIndex);
    UNREFERENCED(endIndex);
  }

  SpawnRulePtr::SpawnRulePtr(std::nullptr_t) :
    ptr_(nullptr)
  {
  }

  SpawnRulePtr::SpawnRulePtr(std::shared_ptr<SpawnRule> ptr) :
    ptr_(ptr)
  {
  }

  SpawnRulePtr::SpawnRulePtr(const SpawnRulePtr& other) :
    ptr_(other->Clone())
  {
  }

  SpawnRulePtr& SpawnRulePtr::operator=(const SpawnRulePtr& other)
  {
    ptr_ = other->Clone();

    return *this;
  }

  SpawnRulePtr::SpawnRulePtr(SpawnRulePtr&& other) noexcept :
    ptr_(std::move(other.ptr_))
  {
  }

  SpawnRulePtr& SpawnRulePtr::operator=(SpawnRulePtr&& other) noexcept
  {
    if (this != &other) // Prevent self-assignment
    {
      ptr_ = std::move(other.ptr_);
    }

    return *this;
  }

  SpawnRule* SpawnRulePtr::operator->() const
  {
    return ptr_.operator->();
  }

  SpawnRule& SpawnRulePtr::operator*() const
  {
    return *ptr_;
  }

  SpawnRulePtr::operator bool() const noexcept
  {
    return static_cast<bool>(ptr_);
  }
}