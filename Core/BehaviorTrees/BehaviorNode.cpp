/* ======================================================================== */
/*!
 * \file            BehaviorNode.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "stdafx.h"
#include "BehaviorNode.hpp"

namespace Barrage
{
  BehaviorNode::BehaviorNode(const std::string& name, unsigned maxChildren) :
    parentIndex_(0),
    maxChildren_(maxChildren),
    childIndices_(),
    name_(name)
  {
  }

  const std::string& BehaviorNode::GetName() const
  {
    return name_;
  }

  unsigned BehaviorNode::GetParentIndex() const
  {
    return parentIndex_;
  }

  unsigned BehaviorNode::GetMaxChildren() const
  {
    return maxChildren_;
  }

  void BehaviorNode::SetParentIndex(unsigned index)
  {
    parentIndex_ = index;
  }

  BehaviorState BehaviorNode::Execute(BehaviorNodeInfo& info)
  {
    UNREFERENCED(info);

    return BehaviorState::Success;
  }
  
  rttr::variant BehaviorNode::GetRTTRValue()
  {
    return rttr::variant();
  }

  void BehaviorNode::SetRTTRValue(const rttr::variant& value)
  {
    UNREFERENCED(value);
  }

  bool BehaviorNode::HasArray()
  {
    return false;
  }

  BehaviorNodeWithArray::BehaviorNodeWithArray(
    const std::string& name, 
    unsigned maxChildren
  ) : 
    BehaviorNode(name, maxChildren)
  {
  }

  bool BehaviorNodeWithArray::HasArray()
  {
    return true;
  }

  BehaviorNodeDeepPtr::BehaviorNodeDeepPtr(std::nullptr_t) :
    ptr_(nullptr)
  {
  }

  BehaviorNodeDeepPtr::BehaviorNodeDeepPtr(std::shared_ptr<BehaviorNode> ptr) :
    ptr_(ptr)
  {
  }

  BehaviorNodeDeepPtr::BehaviorNodeDeepPtr(const BehaviorNodeDeepPtr& other) :
    ptr_(other ? other->Clone() : nullptr)
  {
  }

  BehaviorNodeDeepPtr& BehaviorNodeDeepPtr::operator=(const BehaviorNodeDeepPtr& other)
  {
    if (this != &other) // Prevent self-assignment
    {
      ptr_ = other ? other->Clone() : nullptr;
    }

    return *this;
  }

  BehaviorNodeDeepPtr::BehaviorNodeDeepPtr(BehaviorNodeDeepPtr&& other) noexcept :
    ptr_(std::move(other.ptr_))
  {
  }

  BehaviorNodeDeepPtr& BehaviorNodeDeepPtr::operator=(BehaviorNodeDeepPtr&& other) noexcept
  {
    if (this != &other) // Prevent self-assignment
    {
      ptr_ = std::move(other.ptr_);
    }

    return *this;
  }

  BehaviorNode* BehaviorNodeDeepPtr::operator->() const
  {
    return ptr_.operator->();
  }

  BehaviorNode& BehaviorNodeDeepPtr::operator*() const
  {
    return *ptr_;
  }

  BehaviorNodeDeepPtr::operator bool() const noexcept
  {
    return static_cast<bool>(ptr_);
  }

  std::shared_ptr<BehaviorNode> BehaviorNodeDeepPtr::Get()
  {
    return ptr_;
  }
}