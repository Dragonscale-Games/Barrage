/* ======================================================================== */
/*!
 * \file            PositionRules.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Spawn rules that set the initial position of an object.
 */
 /* ======================================================================== */

#include "SpeedRules.hpp"
#include <Engine/Engine.hpp>
#include "ComponentArrays/VelocityArray.hpp"
#include <stdafx.h>

namespace Barrage
{
  namespace Spawn
  {
    RandomSpeed::RandomSpeed() : SpawnRuleT<RandomSpeedData>("RandomSpeed") {}
  
    void RandomSpeed::Execute(Pool& initPool, Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices)
    {
      Barrage::Random& rng = destPool.GetSpace().GetRNG();
      VelocityArray& dest_velocities = *destPool.GetComponentArray<Velocity>("Velocity");
  
      for (unsigned i = 0; i < numNewObjects; ++i)
      {
        unsigned dest_index = i + firstObjIndex;
        Velocity& dest_velocity = dest_velocities.Data(dest_index);

        glm::vec2 velocity(dest_velocity.vx_, dest_velocity.vy_);
        glm::vec2 direction = glm::normalize(velocity);
        velocity = rng.RangeFloat(data_.minSpeed_, data_.maxSpeed_) * direction;

        dest_velocity.vx_ = velocity.x;
        dest_velocity.vy_ = velocity.y;
      }
    }

    void RandomSpeed::SetRTTRValue(const rttr::variant& value)
    {
      SpawnRuleT<RandomSpeedData>::SetRTTRValue(value);

      if (data_.minSpeed_ < MINIMUM_SPEED)
      {
        data_.minSpeed_ = MINIMUM_SPEED;
      }

      if (data_.maxSpeed_ < data_.minSpeed_)
      {
        data_.maxSpeed_ = data_.minSpeed_;
      }
    }
  }
}