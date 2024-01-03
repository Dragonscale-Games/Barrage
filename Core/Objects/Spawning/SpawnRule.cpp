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

  bool SpawnRuleWithArray::HasArray()
  {
    return true;
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

  std::shared_ptr<SpawnRule> SpawnRulePtr::Get()
  {
    return ptr_;
  }

  SpawnRuleCollection::SpawnRuleCollection() :
    basicRules_(),
    arrayRules_()
  {
  }

  void SpawnRuleCollection::AddSpawnRule(SpawnRulePtr spawnRule)
  {
    if (spawnRule->HasArray())
    {
      arrayRules_.push_back(spawnRule);
    }
    else
    {
      basicRules_.push_back(spawnRule);
    }
  }

  void SpawnRuleCollection::SetCapacity(unsigned capacity)
  {
    for (auto it = arrayRules_.begin(); it != arrayRules_.end(); ++it)
    {
      std::shared_ptr<SpawnRuleWithArray> spawnRule = std::static_pointer_cast<SpawnRuleWithArray>(it->Get());

      spawnRule->SetCapacity(capacity);
    }
  }

  void SpawnRuleCollection::HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex)
  {
    for (auto it = arrayRules_.begin(); it != arrayRules_.end(); ++it)
    {
      std::shared_ptr<SpawnRuleWithArray> spawnRule = std::static_pointer_cast<SpawnRuleWithArray>(it->Get());

      spawnRule->HandleDestructions(destructionArray, writeIndex, endIndex);
    }
  }

  size_t SpawnRuleCollection::Size()
  {
    return basicRules_.size() + arrayRules_.size();
  }
}