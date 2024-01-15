#pragma once
/* ======================================================================== */
/*!
 * \file            SpawnMatchPosition.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnMatchPosition.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"
#include "Objects/Pools/Pool.hpp"

namespace Barrage
{
  namespace Spawn
  {
    MatchPosition::MatchPosition() : SpawnRule("MatchPosition") {}

    std::shared_ptr<SpawnRule> MatchPosition::Clone() const
    {
      return std::make_shared<MatchPosition>(*this);
    }

    void MatchPosition::Execute(SpawnRuleInfo& info)
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

            destPosition = sourcePosition;
          }
        }
      }
    }
  }
}