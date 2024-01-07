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

  GenericSpawnRule::GenericSpawnRule(std::nullptr_t) :
    ptr_(nullptr)
  {
  }

  GenericSpawnRule::GenericSpawnRule(std::shared_ptr<SpawnRule> ptr) :
    ptr_(ptr)
  {
  }

  GenericSpawnRule::GenericSpawnRule(const GenericSpawnRule& other) :
    ptr_(other ? other->Clone() : nullptr)
  {
  }

  GenericSpawnRule& GenericSpawnRule::operator=(const GenericSpawnRule& other)
  {
    ptr_ = other ? other->Clone() : nullptr;

    return *this;
  }

  GenericSpawnRule::GenericSpawnRule(GenericSpawnRule&& other) noexcept :
    ptr_(std::move(other.ptr_))
  {
  }

  GenericSpawnRule& GenericSpawnRule::operator=(GenericSpawnRule&& other) noexcept
  {
    if (this != &other) // Prevent self-assignment
    {
      ptr_ = std::move(other.ptr_);
    }

    return *this;
  }

  SpawnRule* GenericSpawnRule::operator->() const
  {
    return ptr_.operator->();
  }

  SpawnRule& GenericSpawnRule::operator*() const
  {
    return *ptr_;
  }

  GenericSpawnRule::operator bool() const noexcept
  {
    return static_cast<bool>(ptr_);
  }

  std::shared_ptr<SpawnRule> GenericSpawnRule::Get()
  {
    return ptr_;
  }

  SpawnRuleCollection::SpawnRuleCollection() :
    spawnRules_()
  {
  }

  void SpawnRuleCollection::AddSpawnRule(GenericSpawnRule spawnRule)
  {
    spawnRules_.push_back(spawnRule);
  }

  void SpawnRuleCollection::SetCapacity(unsigned capacity)
  {
    for (auto it = spawnRules_.begin(); it != spawnRules_.end(); ++it)
    {
      GenericSpawnRule& spawnRule = *it;
    
      if (spawnRule->HasArray())
      {
        std::shared_ptr<SpawnRuleWithArray> spawnRulePtr = std::static_pointer_cast<SpawnRuleWithArray>(spawnRule.Get());
    
        spawnRulePtr->SetCapacity(capacity);
      }
    }
  }

  void SpawnRuleCollection::HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex)
  {
    for (auto it = spawnRules_.begin(); it != spawnRules_.end(); ++it)
    {
      GenericSpawnRule& spawnRule = *it;
      
      if (spawnRule->HasArray())
      {
        std::shared_ptr<SpawnRuleWithArray> spawnRulePtr = std::static_pointer_cast<SpawnRuleWithArray>(spawnRule.Get());

        spawnRulePtr->HandleDestructions(destructionArray, writeIndex, endIndex);
      }
    }
  }

  size_t SpawnRuleCollection::Size()
  {
    return spawnRules_.size();
  }

  void SpawnRuleCollection::ApplyRules(
    Pool& sourcePool,
    Pool& destinationPool,
    Space& space,
    unsigned startIndex,
    std::vector<unsigned>& sourceIndices,
    ComponentArrayT<GroupInfo>& groupInfoArray
  )
  {
    for (auto it = spawnRules_.begin(); it != spawnRules_.end(); ++it)
    {
      GenericSpawnRule& spawnRule = *it;

      spawnRule->ExecuteFull(sourcePool, destinationPool, space, startIndex, sourceIndices, groupInfoArray);
    }
  }
}