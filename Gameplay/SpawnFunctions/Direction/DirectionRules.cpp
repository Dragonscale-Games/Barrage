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
#include "Utilities/Utilities.hpp"
#include "ComponentArrays/VelocityArray.hpp"

namespace Barrage
{
  namespace Spawn
  {
    RandomDirection::RandomDirection() : SpawnRule("RandomDirection") {}
    
    void RandomDirection::Execute(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices)
    {
      Barrage::Random& rng = destPool.GetSpace().GetRNG();
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

    SetDirection::SetDirection() : SpawnRuleT<SetDirectionData>("SetDirection") {};

    void SetDirection::Execute(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices)
    {
      VelocityArray& dest_velocities = *destPool.GetComponentArray<Velocity>("Velocity");

      for (unsigned i = 0; i < numNewObjects; ++i)
      {
        unsigned dest_index = i + firstObjIndex;
        Velocity& velocity = dest_velocities.Data(dest_index);
        float speed = glm::length(glm::vec2(velocity.vx_, velocity.vy_));

        velocity.vx_ = speed * data_.xDirection_;
        velocity.vy_ = speed * data_.yDirection_;
      }
    }

    void SetDirection::SetRTTRValue(const rttr::variant& value)
    {
      SpawnRuleT<SetDirectionData>::SetRTTRValue(value);

      data_.xDirection_ = glm::cos(data_.angle_);
      data_.yDirection_ = glm::sin(data_.angle_);
    }

    Spiral::Spiral() : SpawnRuleTA<SpiralData, SpiralArrayElement>("Spiral") {};

    void Spiral::Execute(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices)
    {
      VelocityArray& dest_velocities = *destPool.GetComponentArray<Velocity>("Velocity");
      
      for (unsigned i = 0; i < numNewObjects; ++i)
      {
        unsigned dest_index = i + firstObjIndex;
        unsigned sourceIndex = sourceIndices[i];

        Velocity& velocity = dest_velocities.Data(dest_index);
        float angle = dataArray_.Data(sourceIndex).angle_;
        Velocity original_velocity = velocity;
        
        float cosAngle = glm::cos(angle);
        float sinAngle = glm::sin(angle);

        velocity.vx_ = original_velocity.vx_ * cosAngle - original_velocity.vy_ * sinAngle;
        velocity.vy_ = original_velocity.vx_ * sinAngle + original_velocity.vy_ * cosAngle;
      }

      for (unsigned i = 0; i < initPool.GetActiveObjectCount(); ++i)
      {
        float& angle = dataArray_.Data(i).angle_;

        angle = ClampWrapped(angle + data_.angleDelta_, 0.0f, 2.0f * 3.1415926f);
      }
    }
  }
}