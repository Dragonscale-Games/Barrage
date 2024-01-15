#pragma once
/* ======================================================================== */
/*!
 * \file            SpawnOffsetGlobal.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnOffsetGlobal.hpp"
#include "Objects/Pools/Pool.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"

namespace Barrage
{
  namespace Spawn
  {
    OffsetGlobal::OffsetGlobal() : SpawnRuleT<OffsetGlobalData>("OffsetGlobal") {}

    std::shared_ptr<SpawnRule> OffsetGlobal::Clone() const
    {
      return std::make_shared<OffsetGlobal>(*this);
    }

    void OffsetGlobal::Execute(SpawnRuleInfo& info)
    {
      PositionArray& dest_positions = info.destinationPool_.GetComponentArray<Position>("Position");

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          glm::vec2 offset = data_.base_ + static_cast<float>(group) * data_.delta_;

          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned dest_index = CalculateDestinationIndex(info, object, group, layerCopy);
            Position& position = dest_positions.Data(dest_index);

            position.x_ += offset.x;
            position.y_ += offset.y;
          }
        }
      }
    }

    void OffsetGlobal::Reflect()
    {
      rttr::registration::class_<Spawn::OffsetGlobalData>("OffsetGlobalData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("base", &Spawn::OffsetGlobalData::base_)
        .property("delta", &Spawn::OffsetGlobalData::delta_)
        ;
    }
  }
}