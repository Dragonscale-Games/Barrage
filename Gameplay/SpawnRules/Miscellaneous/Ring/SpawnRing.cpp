 
/* ======================================================================== */
/*!
 * \file            SpawnRing.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnRing.hpp"
#include "Objects/Pools/Pool.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  namespace Spawn
  {
    Ring::Ring() : SpawnRule("Ring") {}

    std::shared_ptr<SpawnRule> Ring::Clone() const
    {
      return std::make_shared<Ring>(*this);
    }

    void Ring::Execute(SpawnRuleInfo& info)
    {
      if (info.groupInfo_.numGroups_ == 0)
      {
        return;
      }
      
      float spacing = (2.0f * BARRAGE_PI) / info.groupInfo_.numGroups_;

      PositionArray& dest_positions = info.destinationPool_.GetComponentArray<Position>("Position");
      VelocityArray& dest_velocities = info.destinationPool_.GetComponentArray<Velocity>("Velocity");

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          float angle = group * spacing;
          float cos_angle = glm::cos(angle);
          float sin_angle = glm::sin(angle);

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