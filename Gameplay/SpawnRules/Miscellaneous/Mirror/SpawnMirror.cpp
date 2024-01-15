#pragma once
/* ======================================================================== */
/*!
 * \file            SpawnMirror.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnMirror.hpp"
#include "Objects/Pools/Pool.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"

namespace Barrage
{
  namespace Spawn
  {
    Mirror::Mirror() : SpawnRule("Mirror") {}

    std::shared_ptr<SpawnRule> Mirror::Clone() const
    {
      return std::make_shared<Mirror>(*this);
    }

    void Mirror::Execute(SpawnRuleInfo& info)
    {
      const Position& origin = info.sourcePool_.GetComponentArray<Position>("Position").Data(info.sourceIndex_);
      
      PositionArray& dest_positions = info.destinationPool_.GetComponentArray<Position>("Position");
      VelocityArray& dest_velocities = info.destinationPool_.GetComponentArray<Velocity>("Velocity");

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 1; group < info.groupInfo_.numGroups_; group += 2)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned dest_index = CalculateDestinationIndex(info, object, group, layerCopy);
            Position& position = dest_positions.Data(dest_index);
            Velocity& velocity = dest_velocities.Data(dest_index);

            position.x_ = 2.0f * origin.x_ - position.x_;
            velocity.vx_ = -velocity.vx_;
          }
        }
      }
    }
  }
}