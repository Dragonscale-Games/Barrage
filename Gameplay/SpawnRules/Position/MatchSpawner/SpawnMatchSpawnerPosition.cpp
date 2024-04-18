 
/* ======================================================================== */
/*!
 * \file            SpawnMatchSpawnerPosition.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnMatchSpawnerPosition.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"
#include "Objects/Pools/Pool.hpp"

namespace Barrage
{
  namespace Spawn
  {
    MatchSpawnerPosition::MatchSpawnerPosition() : SpawnRule("MatchSpawnerPosition") {}

    std::shared_ptr<SpawnRule> MatchSpawnerPosition::Clone() const
    {
      return std::make_shared<MatchSpawnerPosition>(*this);
    }

    void MatchSpawnerPosition::Execute(SpawnRuleInfo& info)
    {
      Position& sourcePosition = info.sourcePool_.GetComponentArray<Position>("Position").Data(info.sourceIndex_);
      PositionArray& destPositions = info.destinationPool_.GetComponentArray<Position>("Position");

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned destIndex = CalculateDestinationIndex(info, object, group, layerCopy);
            Position& destPosition = destPositions.Data(destIndex);

            destPosition.x_ += sourcePosition.x_;
            destPosition.y_ += sourcePosition.y_;
          }
        }
      }
    }
  }
}