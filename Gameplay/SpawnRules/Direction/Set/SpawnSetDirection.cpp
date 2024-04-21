/* ======================================================================== */
/*!
 * \file            SpawnSetDirection.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Applies a constant direction to a spawned object.

   Requirements:
   - Velocity (destination)
 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnSetDirection.hpp"
#include "Objects/Pools/Pool.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"

namespace Barrage
{
  namespace Spawn
  {
    SetDirection::SetDirection() : SpawnRuleT<SetDirectionData>("SetDirection") {}

    std::shared_ptr<SpawnRule> SetDirection::Clone() const
    {
      return std::make_shared<SetDirection>(*this);
    }

    void SetDirection::Execute(SpawnRuleInfo& info)
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

            dest_velocity.SetAngle(data_.angle_);
          }
        }
      }
    }

    void SetDirection::Reflect()
    {
      rttr::registration::class_<Spawn::SetDirectionData>("SetDirectionData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("angle", &Spawn::SetDirectionData::angle_)
        ;
    }
  }
}