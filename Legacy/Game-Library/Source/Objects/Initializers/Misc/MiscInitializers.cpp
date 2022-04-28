/* ======================================================================== */
/*!
 * \file            MiscInitializers.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here>

 */
 /* ======================================================================== */

#include "stdafx.h"
#include "MiscInitializers.hpp"
#include "Objects/Components/GameComponents.hpp"
#include "Random/Random.hpp"

namespace Barrage
{
  namespace Initializers
  {
    void CircleSpawn(Pool& initPool, Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects)
    {
      Position* positions = dynamic_cast<Position*>(destPool.objectComponents_["Position"]);
      Timer* timer = dynamic_cast<Timer*>(initPool.poolComponents_["Timer"]);

      glm::vec2 spawn_position;

      spawn_position.x = 640.0f + 120.0f * glm::cos(timer->timer_ * 0.1f);
      spawn_position.y = 540.0f + 120.0f * glm::sin(timer->timer_ * 0.11f);

      for (unsigned i = 0; i < numNewObjects; ++i)
      {
        positions->data_[i + firstObjIndex].position_ = spawn_position;
      }
    }

    void RandomDirection(Pool& initPool, Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects)
    {
      RNG* rng_component = dynamic_cast<RNG*>(initPool.poolComponents_["RNG"]);
      Random& rng = rng_component->rng_;

      Velocity* velocities = dynamic_cast<Velocity*>(destPool.objectComponents_["Velocity"]);

      for (unsigned i = 0; i < numNewObjects; ++i)
      {
        float angle = glm::radians(rng.RangeFloat(0, 360.0f));
        velocities->data_[i + firstObjIndex].velocity_.x = 3.0f * glm::cos(angle);
        velocities->data_[i + firstObjIndex].velocity_.y = 3.0f * glm::sin(angle);
      }
    }
  }
}