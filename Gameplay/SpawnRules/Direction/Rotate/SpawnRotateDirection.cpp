/* ======================================================================== */
/*!
 * \file            SpawnRotateDirection.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Applies a rotation to a spawned object's direction.

   Requirements:
   - Velocity (destination)
 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnRotateDirection.hpp"
#include "glm/glm.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"
#include "Objects/Pools/Pool.hpp"

namespace Barrage
{
  namespace Spawn
  {
    RotateDirection::RotateDirection() : SpawnRuleT<RotateDirectionData>("RotateDirection") {}
    
    std::shared_ptr<SpawnRule> RotateDirection::Clone() const
    {
      return std::make_shared<RotateDirection>(*this);
    }
    
    void RotateDirection::Execute(SpawnRuleInfo& info)
    {
      VelocityArray& dest_velocities = info.destinationPool_.GetComponentArray<Velocity>("Velocity");
    
      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned dest_index = CalculateDestinationIndex(info, object, group, layerCopy);
            Velocity& velocity = dest_velocities.Data(dest_index);
            Velocity original_velocity = velocity;

            velocity.vx_ = original_velocity.vx_ * data_.cosineAngle_ - original_velocity.vy_ * data_.sinAngle_;
            velocity.vy_ = original_velocity.vx_ * data_.sinAngle_ + original_velocity.vy_ * data_.cosineAngle_;
          }
        }
      }
    }

    void RotateDirection::SetRTTRValue(const rttr::variant& value)
    {
      SpawnRuleT<RotateDirectionData>::SetRTTRValue(value);

      data_.cosineAngle_ = glm::cos(data_.angle_.value_);
      data_.sinAngle_ = glm::sin(data_.angle_.value_);
    }

    void RotateDirection::Reflect()
    {
      rttr::registration::class_<Spawn::RotateDirectionData>("RotateDirectionData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("angle", &Spawn::RotateDirectionData::angle_)
        ;
    }
  }
}