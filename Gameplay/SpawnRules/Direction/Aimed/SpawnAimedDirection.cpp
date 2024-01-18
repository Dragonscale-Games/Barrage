
/* ======================================================================== */
/*!
 * \file            SpawnAimedDirection.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnAimedDirection.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"
#include "Objects/Pools/Pool.hpp"
#include "Spaces/Space.hpp"
#include "glm/glm.hpp"

namespace Barrage
{
  namespace Spawn
  {
    AimedDirection::AimedDirection() : SpawnRule("AimedDirection") {}

    std::shared_ptr<SpawnRule> AimedDirection::Clone() const
    {
      return std::make_shared<AimedDirection>(*this);
    }

    void AimedDirection::Execute(SpawnRuleInfo& info)
    {
      if (info.space_.GetObjectManager().pools_.count("Player Pool") == 0)
      {
        return;
      }
      
      Pool& player_pool = info.space_.GetObjectManager().pools_.at("Player Pool");

      if (player_pool.ActiveObjectCount() == 0)
      {
        return;
      }

      const Position& player_position = player_pool.GetComponentArray<Position>("Position").Data(0);
      const Position& source_position = info.sourcePool_.GetComponentArray<Position>("Position").Data(info.sourceIndex_);

      glm::vec2 delta_position(player_position.x_ - source_position.x_, player_position.y_ - source_position.y_);

      if (glm::length(delta_position) < 0.0000001f)
      {
        return;
      }

      VelocityArray& destVelocities = info.destinationPool_.GetComponentArray<Velocity>("Velocity");

      float angle = Velocity(delta_position.x, delta_position.y).GetAngle();
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

            destVelocity.Rotate(cos_angle, sin_angle);
          }
        }
      }
    }
  }
}