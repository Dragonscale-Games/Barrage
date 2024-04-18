
/* ======================================================================== */
/*!
 * \file            SpawnMatchSpawnerDirection.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnMatchSpawnerDirection.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"
#include "Objects/Pools/Pool.hpp"
#include "glm/glm.hpp"

namespace Barrage
{
  namespace Spawn
  {
    MatchSpawnerDirection::MatchSpawnerDirection() : SpawnRule("MatchSpawnerDirection") {}

    std::shared_ptr<SpawnRule> MatchSpawnerDirection::Clone() const
    {
      return std::make_shared<MatchSpawnerDirection>(*this);
    }

    void MatchSpawnerDirection::Execute(SpawnRuleInfo& info)
    {
      Velocity& sourceVelocity = info.sourcePool_.GetComponentArray<Velocity>("Velocity").Data(info.sourceIndex_);
      VelocityArray& destVelocities = info.destinationPool_.GetComponentArray<Velocity>("Velocity");

      float angle = sourceVelocity.GetAngle();
      float cos_angle = glm::cos(angle);
      float sin_angle = glm::sin(angle);

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned destIndex = CalculateDestinationIndex(info, object, group, layerCopy);
            Velocity& destVelocity = destVelocities.Data(destIndex);
            float speed = glm::length(glm::vec2(destVelocity.vx_, destVelocity.vy_));

            destVelocity.vx_ = speed * cos_angle;
            destVelocity.vy_ = speed * sin_angle;
          }
        }
      }
    }
  }
}