/* ======================================================================== */
/*!
 * \file            SpawnSetPosition.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnSetPosition.hpp"
#include "Objects/Pools/Pool.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"

namespace Barrage
{
  namespace Spawn
  {
    SetPosition::SetPosition() : SpawnRuleT<SetPositionData>("SetPosition") {}

    std::shared_ptr<SpawnRule> SetPosition::Clone() const
    {
      return std::make_shared<SetPosition>(*this);
    }

    void SetPosition::Execute(SpawnRuleInfo& info)
    {
      PositionArray& destPositions = info.destinationPool_.GetComponentArray<Position>("Position");

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned destIndex = CalculateDestinationIndex(info, object, group, layerCopy);
            Position& destPosition = destPositions.Data(destIndex);

            destPosition.x_ = data_.position_.x;
            destPosition.y_ = data_.position_.y;
          }
        }
      }
    }

    void SetPosition::Reflect()
    {
      rttr::registration::class_<Spawn::SetPositionData>("SetPositionData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("position", &Spawn::SetPositionData::position_)
        ;
    }
  }
}