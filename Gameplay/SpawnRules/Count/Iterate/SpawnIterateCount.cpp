
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
      int new_count = info.groupInfo_.numGroups_ + data_.amount_;
      
      if (new_count >= data_.min_ && new_count <= data_.max_)
      {
        info.groupInfo_.numGroups_ = new_count;
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
        .property("amount", &Spawn::IterateCountData::amount_)
        .property("min", &Spawn::IterateCountData::min_)
        .property("max", &Spawn::IterateCountData::max_)
        ;
    }
  }
}