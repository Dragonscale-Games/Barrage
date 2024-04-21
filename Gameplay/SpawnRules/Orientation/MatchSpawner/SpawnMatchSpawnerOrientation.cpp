
/* ======================================================================== */
/*!
 * \file            SpawnMatchSpawnerOrientation.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnMatchSpawnerOrientation.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"
#include "Objects/Pools/Pool.hpp"
#include "glm/glm.hpp"

namespace Barrage
{
  namespace Spawn
  {
    MatchSpawnerOrientation::MatchSpawnerOrientation() : SpawnRule("MatchSpawnerOrientation") {}

    std::shared_ptr<SpawnRule> MatchSpawnerOrientation::Clone() const
    {
      return std::make_shared<MatchSpawnerOrientation>(*this);
    }

    void MatchSpawnerOrientation::Execute(SpawnRuleInfo& info)
    {
      Velocity& sourceVelocity = info.sourcePool_.GetComponentArray<Velocity>("Velocity").Data(info.sourceIndex_);
      PositionArray& destPositions = info.destinationPool_.GetComponentArray<Position>("Position");
      VelocityArray& destVelocities = info.destinationPool_.GetComponentArray<Velocity>("Velocity");

      float angle = sourceVelocity.GetAngle().value_;
      float cosAngle = glm::cos(angle);
      float sinAngle = glm::sin(angle);

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned destIndex = CalculateDestinationIndex(info, object, group, layerCopy);
            Position& destPosition = destPositions.Data(destIndex);
            Velocity& destVelocity = destVelocities.Data(destIndex);

            destPosition.Rotate(cosAngle, sinAngle);
            destVelocity.Rotate(angle);
          }
        }
      }
    }
  }
}