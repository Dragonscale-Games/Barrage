/* ======================================================================== */
/*!
 * \file            SpawnRandomOrientation.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Applies a random orientation to an entire layer of objects.

   Requirements:
   -Position (destination)
   -Velocity (destination)
 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnRandomOrientation.hpp"
#include "Random/Random.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"
#include "Spaces/Space.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  namespace Spawn
  {
    RandomOrientation::RandomOrientation() : SpawnRule("RandomOrientation") {}

    std::shared_ptr<SpawnRule> RandomOrientation::Clone() const
    {
      return std::make_shared<RandomOrientation>(*this);
    }

    void RandomOrientation::Execute(SpawnRuleInfo& info)
    {
      Random& rng = info.space_.RNG();
      PositionArray& dest_positions = info.destinationPool_.GetComponentArray<Position>("Position");
      VelocityArray& dest_velocities = info.destinationPool_.GetComponentArray<Velocity>("Velocity");

      for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
      {
        float angle = BARRAGE_PI * rng.RangeFloat(0, 2.0f);
        float cos_angle = glm::cos(angle);
        float sin_angle = glm::sin(angle);

        for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned dest_index = CalculateDestinationIndex(info, object, group, layerCopy);
            Position& dest_position = dest_positions.Data(dest_index);
            Velocity& dest_velocity = dest_velocities.Data(dest_index);

            dest_position.Rotate(cos_angle, sin_angle);
            dest_velocity.Rotate(angle);
          }
        }
      }
    }
  }
}