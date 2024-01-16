/* ======================================================================== */
/*!
 * \file            SpawnOffsetPosition.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnOffsetPosition.hpp"
#include "Objects/Pools/Pool.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"

namespace Barrage
{
  namespace Spawn
  {
    OffsetPosition::OffsetPosition() : SpawnRuleT<OffsetPositionData>("OffsetPosition") {}

    std::shared_ptr<SpawnRule> OffsetPosition::Clone() const
    {
      return std::make_shared<OffsetPosition>(*this);
    }

    void OffsetPosition::Execute(SpawnRuleInfo& info)
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

    void OffsetPosition::Reflect()
    {
      rttr::registration::class_<Spawn::OffsetPositionData>("OffsetPositionData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("base", &Spawn::OffsetPositionData::base_)
        .property("delta", &Spawn::OffsetPositionData::delta_)
        ;
    }
  }
}