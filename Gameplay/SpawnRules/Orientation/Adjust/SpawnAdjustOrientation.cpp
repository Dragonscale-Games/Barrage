/* ======================================================================== */
/*!
 * \file            SpawnAdjustOrientation.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Rotates the orientation of an entire layer of objects.

   Requirements:
   - Position (destination)
   - Velocity (destination)
 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnAdjustOrientation.hpp"
#include "Objects/Pools/Pool.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"

namespace Barrage
{
  namespace Spawn
  {
    AdjustOrientation::AdjustOrientation() : SpawnRuleT<AdjustOrientationData>("AdjustOrientation") {}

    std::shared_ptr<SpawnRule> AdjustOrientation::Clone() const
    {
      return std::make_shared<AdjustOrientation>(*this);
    }

    void AdjustOrientation::Execute(SpawnRuleInfo& info)
    {
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

            dest_position.Rotate(data_.cosineAngle_, data_.sinAngle_);
            dest_velocity.Rotate(data_.angle_.value_);
          }
        }
      }
    }

    void AdjustOrientation::SetRTTRValue(const rttr::variant& value)
    {
      SpawnRuleT<AdjustOrientationData>::SetRTTRValue(value);

      data_.cosineAngle_ = glm::cos(data_.angle_.value_);
      data_.sinAngle_ = glm::sin(data_.angle_.value_);
    }

    void AdjustOrientation::Reflect()
    {
      rttr::registration::class_<Spawn::AdjustOrientationData>("AdjustOrientationData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("angle", &Spawn::AdjustOrientationData::angle_)
        ;
    }
  }
}