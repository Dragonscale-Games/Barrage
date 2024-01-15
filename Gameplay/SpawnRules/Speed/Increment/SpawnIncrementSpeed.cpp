#pragma once
/* ======================================================================== */
/*!
 * \file            SpawnIncrementSpeed.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnIncrementSpeed.hpp"
#include "Objects/Pools/Pool.hpp"
#include "glm/glm.hpp"

namespace Barrage
{
  namespace Spawn
  {
    IncrementSpeed::IncrementSpeed() : SpawnRuleT<IncrementSpeedData>("IncrementSpeed") {}

    std::shared_ptr<SpawnRule> IncrementSpeed::Clone() const
    {
      return std::make_shared<IncrementSpeed>(*this);
    }

    void IncrementSpeed::Execute(SpawnRuleInfo& info)
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
            
            glm::vec2 velocity(dest_velocity.vx_, dest_velocity.vy_);
            glm::vec2 direction = glm::normalize(velocity);
            velocity = speed * direction;

            dest_velocity.vx_ = velocity.x;
            dest_velocity.vy_ = velocity.y;
          }
        }
      }
    }

    void IncrementSpeed::Reflect()
    {
      rttr::registration::class_<Spawn::IncrementSpeedData>("IncrementSpeedData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("base", &Spawn::IncrementSpeedData::base_)
        .property("delta", &Spawn::IncrementSpeedData::delta_)
        ;
    }
  }
}