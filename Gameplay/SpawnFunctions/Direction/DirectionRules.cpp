/* ======================================================================== */
/*!
 * \file            DirectionFuncs.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Spawn functions that set the initial direction of an object's velocity.
 */
 /* ======================================================================== */

#include "DirectionRules.hpp"
#include <Engine/Engine.hpp>
#include <stdafx.h>

#include "ComponentArrays/VelocityArray.hpp"

namespace Barrage
{
  namespace Spawn
  {
    RandomDirection::RandomDirection() : SpawnRule("RandomDirection") {}
    
    void RandomDirection::Execute(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices)
    {
      Barrage::Random& rng = initPool.GetSpace().GetRNG();
      VelocityArray& dest_velocities = *destPool.GetComponentArray<Velocity>("Velocity");

      for (unsigned i = 0; i < numNewObjects; ++i)
      {
        unsigned dest_index = i + firstObjIndex;
        Velocity& velocity = dest_velocities.Data(dest_index);
        float speed = glm::length(glm::vec2(velocity.vx_, velocity.vy_));
        float angle = 3.1415926f * rng.RangeFloat(0, 2.0f);

        velocity.vx_ = speed * glm::cos(angle);
        velocity.vy_ = speed * glm::sin(angle);
      }
    }

    RotateDirection::RotateDirection() : SpawnRuleT<RotateDirectionData>("RotateDirection") {};

    void RotateDirection::Execute(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices)
    {
      VelocityArray& dest_velocities = *destPool.GetComponentArray<Velocity>("Velocity");

      for (unsigned i = 0; i < numNewObjects; ++i)
      {
        unsigned dest_index = i + firstObjIndex;
        Velocity& velocity = dest_velocities.Data(dest_index);
        Velocity original_velocity = velocity;

        velocity.vx_ = original_velocity.vx_ * data_.cosineAngle_ - original_velocity.vy_ * data_.sinAngle_;
        velocity.vy_ = original_velocity.vx_ * data_.sinAngle_ + original_velocity.vy_ * data_.cosineAngle_;
      }
    }

    void RotateDirection::SetRTTRValue(const rttr::variant& value)
    {
      SpawnRuleT<RotateDirectionData>::SetRTTRValue(value);

      data_.cosineAngle_ = glm::cos(data_.angle_);
      data_.sinAngle_ = glm::sin(data_.angle_);
    }
  }
}