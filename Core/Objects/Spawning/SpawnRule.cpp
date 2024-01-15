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

#include "stdafx.h"
#include "SpawnRule.hpp"

namespace Barrage
{
  SpawnRule::SpawnRule(const std::string& name) : name_(name)
  {
  }

  const std::string& SpawnRule::GetName() const
  {
    return name_;
  }

  void SpawnRule::ExecuteFull(
    Pool& sourcePool,
    Pool& destinationPool,
    Space& space,
    unsigned startIndex,
    std::vector<unsigned>& sourceIndices,
    ComponentArrayT<GroupInfo>& groupInfoArray
  )
  {
    unsigned currentStartIndex = startIndex;
    
    for (auto it = sourceIndices.begin(); it != sourceIndices.end(); ++it)
    {
      unsigned sourceIndex = *it;
      GroupInfo& groupInfo = groupInfoArray.Data(sourceIndex);
      unsigned currentNumObjects = groupInfo.numGroups_ * groupInfo.numObjectsPerGroup_ * groupInfo.numLayerCopies_;

      SpawnRuleInfo info(sourcePool, destinationPool, space, currentStartIndex, sourceIndex, groupInfo);

      Execute(info);

      currentStartIndex += currentNumObjects;
    }
  }

  rttr::variant SpawnRule::GetRTTRValue()
  {
    return rttr::variant();
  }

  void SpawnRule::SetRTTRValue(const rttr::variant& value)
  {
    UNREFERENCED(value);
  }

  bool SpawnRule::HasArray()
  {
    return false;
  }

  SpawnRuleStage SpawnRule::GetStage()
  {
    return SpawnRuleStage::VALUE_RULE;
  }

  void SpawnRule::Execute(SpawnRuleInfo& info)
  {
    UNREFERENCED(info);
  }

  unsigned SpawnRule::CalculateDestinationIndex(
    SpawnRuleInfo& info, 
    unsigned objectNumber, 
    unsigned groupNumber, 
    unsigned layerCopyNumber)
  {
    unsigned numObjectsPerLayerCopy = info.groupInfo_.numGroups_ * info.groupInfo_.numObjectsPerGroup_;
    unsigned layerOffset = layerCopyNumber * numObjectsPerLayerCopy;
    unsigned groupOffset = groupNumber * info.groupInfo_.numObjectsPerGroup_;

    return info.startIndex_ + layerOffset + groupOffset + objectNumber;
  }

  SpawnRuleWithArray::SpawnRuleWithArray(const std::string& name) : SpawnRule(name)
  {
  }

  bool SpawnRuleWithArray::HasArray()
  {
    return true;
  }

  SpawnRuleDeepPtr::SpawnRuleDeepPtr(std::nullptr_t) :
    ptr_(nullptr)
  {
  }

  SpawnRuleDeepPtr::SpawnRuleDeepPtr(std::shared_ptr<SpawnRule> ptr) :
    ptr_(ptr)
  {
  }

  SpawnRuleDeepPtr::SpawnRuleDeepPtr(const SpawnRuleDeepPtr& other) :
    ptr_(other ? other->Clone() : nullptr)
  {
  }

  SpawnRuleDeepPtr& SpawnRuleDeepPtr::operator=(const SpawnRuleDeepPtr& other)
  {
    ptr_ = other ? other->Clone() : nullptr;

    return *this;
  }

  SpawnRuleDeepPtr::SpawnRuleDeepPtr(SpawnRuleDeepPtr&& other) noexcept :
    ptr_(std::move(other.ptr_))
  {
  }

  SpawnRuleDeepPtr& SpawnRuleDeepPtr::operator=(SpawnRuleDeepPtr&& other) noexcept
  {
    if (this != &other) // Prevent self-assignment
    {
      ptr_ = std::move(other.ptr_);
    }

    return *this;
  }

  SpawnRule* SpawnRuleDeepPtr::operator->() const
  {
    return ptr_.operator->();
  }

  SpawnRule& SpawnRuleDeepPtr::operator*() const
  {
    return *ptr_;
  }

  SpawnRuleDeepPtr::operator bool() const noexcept
  {
    return static_cast<bool>(ptr_);
  }

  std::shared_ptr<SpawnRule> SpawnRuleDeepPtr::Get()
  {
    return ptr_;
  }
}