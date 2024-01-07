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

#include <stdafx.h>
#include "DirectionRules.hpp"
#include "Random/Random.hpp"
#include "ComponentArrays/VelocityArray.hpp"
#include "Spaces/Space.hpp"
#include "glm/glm.hpp"

namespace Barrage
{
  namespace Spawn
  {
    RandomDirection::RandomDirection() : SpawnRule("RandomDirection") {}
    
    std::shared_ptr<SpawnRule> RandomDirection::Clone() const
    {
      return std::make_shared<RandomDirection>(*this);
    }

    void RandomDirection::Execute(SpawnRuleInfo& info)
    {
      Random& rng = info.space_.GetRNG();
      VelocityArray& dest_velocities = info.destinationPool_.GetComponentArray<Velocity>("Velocity");
      
      for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
      {
        float angle = 3.1415926f * rng.RangeFloat(0, 2.0f);

        for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned dest_index = CalculateDestinationIndex(info, object, group, layerCopy);
            Velocity& velocity = dest_velocities.Data(dest_index);
            float speed = glm::length(glm::vec2(velocity.vx_, velocity.vy_));
            
            velocity.vx_ = speed * glm::cos(angle);
            velocity.vy_ = speed * glm::sin(angle);
          }
        }
      }
    }
  }
}