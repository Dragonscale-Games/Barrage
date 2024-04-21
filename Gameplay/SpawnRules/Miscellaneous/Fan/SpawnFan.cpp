 
/* ======================================================================== */
/*!
 * \file            SpawnSpacedFan.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnFan.hpp"
#include "Objects/Pools/Pool.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"

namespace Barrage
{
  namespace Spawn
  {
    Fan::Fan() : SpawnRuleT<FanData>("Fan") {}

    std::shared_ptr<SpawnRule> Fan::Clone() const
    {
      return std::make_shared<Fan>(*this);
    }

    void Fan::Execute(SpawnRuleInfo& info)
    {
      if (info.groupInfo_.numGroups_ == 0)
      {
        return;
      }
      
      float totalAngle = (info.groupInfo_.numGroups_ - 1) * data_.spacing_.value_;
      float startAngle = -(totalAngle / 2.0f);

      PositionArray& dest_positions = info.destinationPool_.GetComponentArray<Position>("Position");
      VelocityArray& dest_velocities = info.destinationPool_.GetComponentArray<Velocity>("Velocity");

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          float angle = startAngle + group * data_.spacing_.value_;
          float cos_angle = glm::cos(angle);
          float sin_angle = glm::sin(angle);

          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned dest_index = CalculateDestinationIndex(info, object, group, layerCopy);
            Position& dest_position = dest_positions.Data(dest_index);
            Velocity& dest_velocity = dest_velocities.Data(dest_index);

            dest_position.Rotate(cos_angle, sin_angle);
            dest_velocity.Rotate(angle);
          }
        }
      }
    }

    void Fan::Reflect()
    {
      rttr::registration::class_<Spawn::FanData>("FanData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("spacing", &Spawn::FanData::spacing_)
        ;
    }
  }
}