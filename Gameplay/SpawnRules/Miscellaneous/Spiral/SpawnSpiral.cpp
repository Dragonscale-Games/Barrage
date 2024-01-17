
/* ======================================================================== */
/*!
 * \file            SpawnSpiral.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnSpiral.hpp"
#include "Objects/Pools/Pool.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"

namespace Barrage
{
  namespace Spawn
  {
    Spiral::Spiral() : SpawnRuleTA<SpiralData, SpiralArrayElement>("Spiral") {}

    std::shared_ptr<SpawnRule> Spiral::Clone() const
    {
      return std::make_shared<Spiral>(*this);
    }

    void Spiral::Execute(SpawnRuleInfo& info)
    {
      float& angle = dataArray_.Data(info.sourceIndex_).angle_.value_;
      float cos_angle = glm::cos(angle);
      float sin_angle = glm::sin(angle);
      angle = ClampWrapped(angle + data_.angleDelta_.value_, 0.0f, 2.0f * 3.1415926f);

      PositionArray& dest_positions = info.destinationPool_.GetComponentArray<Position>("Position");
      VelocityArray& dest_velocities = info.destinationPool_.GetComponentArray<Velocity>("Velocity");

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned dest_index = CalculateDestinationIndex(info, object, group, layerCopy);
            Position& dest_position = dest_positions.Data(dest_index);
            Velocity& dest_velocity = dest_velocities.Data(dest_index);

            dest_position.Rotate(cos_angle, sin_angle);
            dest_velocity.Rotate(cos_angle, sin_angle);
          }
        }
      }
    }

    void Spiral::Reflect()
    {
      rttr::registration::class_<Spawn::SpiralData>("SpiralData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("angleDelta", &Spawn::SpiralData::angleDelta_)
        ;
    }
  }
}