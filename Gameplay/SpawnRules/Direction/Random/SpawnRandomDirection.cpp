/* ======================================================================== */
/*!
 * \file            SpawnRandomDirection.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Applies a random direction to a spawned object.

   Requirements:
   -Position (source)
   -Position (destination)
   -Velocity (destination)
 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnRandomDirection.hpp"
#include "Random/Random.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"
#include "Spaces/Space.hpp"

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
      Random& rng = info.space_.RNG();
      VelocityArray& dest_velocities = info.destinationPool_.GetComponentArray<Velocity>("Velocity");

      for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
      {
        float angle = rng.RangeFloat(0, 2.0f * BARRAGE_PI);

        for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned dest_index = CalculateDestinationIndex(info, object, group, layerCopy);
            Velocity& dest_velocity = dest_velocities.Data(dest_index);
            
            dest_velocity.SetAngle(angle);
          }
        }
      }
    }
  }
}