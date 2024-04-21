
/* ======================================================================== */
/*!
 * \file            SpawnAdjustDirection.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

   Requirements:
   -Velocity (destination)
 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnAdjustDirection.hpp"
#include "Objects/Pools/Pool.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"

namespace Barrage
{
  namespace Spawn
  {
    AdjustDirection::AdjustDirection() : SpawnRuleT<AdjustDirectionData>("AdjustDirection") {}

    std::shared_ptr<SpawnRule> AdjustDirection::Clone() const
    {
      return std::make_shared<AdjustDirection>(*this);
    }

    void AdjustDirection::Execute(SpawnRuleInfo& info)
    {
      VelocityArray& dest_velocities = info.destinationPool_.GetComponentArray<Velocity>("Velocity");

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned dest_index = CalculateDestinationIndex(info, object, group, layerCopy);
            Velocity& dest_velocity = dest_velocities.Data(dest_index);

            dest_velocity.Rotate(data_.angle_.value_);
          }
        }
      }
    }

    void AdjustDirection::Reflect()
    {
      rttr::registration::class_<Spawn::AdjustDirectionData>("AdjustDirectionData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("angle", &Spawn::AdjustDirectionData::angle_)
        ;
    }
  }
}