/* ======================================================================== */
/*!
 * \file            SpawnSetSpeed.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:
   - Velocity (destination)
 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnSetSpeed.hpp"
#include "Objects/Pools/Pool.hpp"
#include "glm/glm.hpp"

namespace Barrage
{
  namespace Spawn
  {
    SetSpeed::SetSpeed() : SpawnRuleT<SetSpeedData>("SetSpeed") {}

    std::shared_ptr<SpawnRule> SetSpeed::Clone() const
    {
      return std::make_shared<SetSpeed>(*this);
    }

    void SetSpeed::Execute(SpawnRuleInfo& info)
    {
      VelocityArray& dest_velocities = info.destinationPool_.GetComponentArray<Velocity>("Velocity");

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          float speed = data_.base_ + group * data_.delta_;
          
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned dest_index = CalculateDestinationIndex(info, object, group, layerCopy);
            Velocity& dest_velocity = dest_velocities.Data(dest_index);
            
            dest_velocity.SetSpeed(speed);
          }
        }
      }
    }

    void SetSpeed::SetRTTRValue(const rttr::variant& value)
    {
      SpawnRuleT<SetSpeedData>::SetRTTRValue(value);

      if (data_.base_ < MINIMUM_SPEED)
      {
        data_.base_ = MINIMUM_SPEED;
      }
    }

    void SetSpeed::Reflect()
    {
      rttr::registration::class_<Spawn::SetSpeedData>("SetSpeedData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("base", &Spawn::SetSpeedData::base_)
        .property("delta", &Spawn::SetSpeedData::delta_)
        ;
    }
  }
}