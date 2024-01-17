
/* ======================================================================== */
/*!
 * \file            SpawnIncrementCount.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnIncrementCount.hpp"
#include "Objects/Pools/Pool.hpp"

namespace Barrage
{
  namespace Spawn
  {
    IncrementCount::IncrementCount() : SpawnRuleT<IncrementCountData>("IncrementCount") {}

    std::shared_ptr<SpawnRule> IncrementCount::Clone() const
    {
      return std::make_shared<IncrementCount>(*this);
    }

    void IncrementCount::Execute(SpawnRuleInfo& info)
    {
      info.groupInfo_.numGroups_ += data_.amount_;
    }

    SpawnRuleStage IncrementCount::GetStage()
    {
      return SpawnRuleStage::COUNT_RULE;
    }

    void IncrementCount::Reflect()
    {
      rttr::registration::class_<Spawn::IncrementCountData>("IncrementCountData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("amount", &Spawn::IncrementCountData::amount_)
        ;
    }
  }
}