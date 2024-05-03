
/* ======================================================================== */
/*!
 * \file            SpawnIterateCount.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnIterateCount.hpp"
#include "Objects/Pools/Pool.hpp"
#include <climits>

namespace Barrage
{
  namespace Spawn
  {
    IterateCount::IterateCount() : SpawnRuleT<IterateCountData>("IterateCount") {}

    std::shared_ptr<SpawnRule> IterateCount::Clone() const
    {
      return std::make_shared<IterateCount>(*this);
    }

    void IterateCount::Execute(SpawnRuleInfo& info)
    {
      long long new_count = static_cast<long long>(info.groupInfo_.numGroups_) + data_.countStep_;
      
      if (new_count >= static_cast<long long>(data_.min_) && new_count <= static_cast<long long>(data_.max_))
      {
        info.groupInfo_.numGroups_ = static_cast<unsigned>(new_count);
      }
    }

    void IterateCount::SetRTTRValue(const rttr::variant& value)
    {
      SpawnRuleT<IterateCountData>::SetRTTRValue(value);
      
      if (data_.max_ < data_.min_)
      {
        data_.max_ = data_.min_;
      }
    }

    SpawnRuleStage IterateCount::GetStage()
    {
      return SpawnRuleStage::COUNT_RULE;
    }

    void IterateCount::Reflect()
    {
      rttr::registration::class_<Spawn::IterateCountData>("IterateCountData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("countStep", &Spawn::IterateCountData::countStep_)
        .property("min", &Spawn::IterateCountData::min_)
        .property("max", &Spawn::IterateCountData::max_)
        ;
    }
  }
}