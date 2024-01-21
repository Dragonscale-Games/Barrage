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
  BehaviorState::State BehaviorState::GetState()
  {
    return state_;
  }

  unsigned BehaviorState::GetNextNodeIndex()
  {
    return nextNodeIndex_;
  }
  
  BehaviorState BehaviorState::Running()
  {
    return BehaviorState(State::Running);
  }

  BehaviorState BehaviorState::Transfer(unsigned nextNodeIndex)
  {
    return BehaviorState(State::Transfer, nextNodeIndex);
  }

  BehaviorState BehaviorState::Success()
  {
    return BehaviorState(State::Success);
  }

  BehaviorState BehaviorState::Failure()
  {
    return BehaviorState(State::Failure);
  }

  BehaviorState::BehaviorState(State state, unsigned nextNodeIndex) :
    state_(state),
    nextNodeIndex_(nextNodeIndex)
  {
  }

  BehaviorNode::BehaviorNode(const std::string& name, BehaviorNodeType type) :
    parentIndex_(BEHAVIOR_END),
    childIndices_(),
    type_(type),
    name_(name)
  {
  }

  const std::string& BehaviorNode::GetName() const
  {
    return name_;
  }

  int BehaviorNode::GetParentIndex() const
  {
    return parentIndex_;
  }

  BehaviorNodeType BehaviorNode::GetType() const
  {
    return type_;
  }

  const std::vector<int>& BehaviorNode::GetChildIndices() const
  {
    return childIndices_;
  }

  void BehaviorNode::SetParentIndex(int index)
  {
    parentIndex_ = index;
  }

  void BehaviorNode::AddChildIndex(int index)
  {
    childIndices_.push_back(index);
  }

  void BehaviorNode::OnBegin(BehaviorNodeInfo& info)
  {
    UNREFERENCED(info);
  }

  BehaviorState BehaviorNode::Execute(BehaviorNodeInfo& info)
  {
    UNREFERENCED(info);

    return BehaviorState::Running();
  }

  void BehaviorNode::OnChildFinish(BehaviorNodeInfo& info, BehaviorState::State result, int childIndex)
  {
    UNREFERENCED(info);
    UNREFERENCED(result);
    UNREFERENCED(childIndex);
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
    BehaviorNodeType type
  ) :
    BehaviorNode(name, type)
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