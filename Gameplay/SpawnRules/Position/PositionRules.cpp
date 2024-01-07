/* ======================================================================== */
/*!
 * \file            PositionRules.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Spawn rules that set the initial position of an object.
 */
 /* ======================================================================== */

#include <stdafx.h>
#include "PositionRules.hpp"
#include "ComponentArrays/PositionArray.hpp"
#include "Random/Random.hpp"
#include "Objects/Pools/Pool.hpp"
#include "Spaces/Space.hpp"

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

    RandomOffset::RandomOffset() : SpawnRuleT<RandomOffsetData>("RandomOffset") {}

    std::shared_ptr<SpawnRule> RandomOffset::Clone() const
    {
      return std::make_shared<RandomOffset>(*this);
    }

    void RandomOffset::Execute(SpawnRuleInfo& info)
    {
      Random& rng = info.space_.GetRNG();
      PositionArray& destPositions = info.destinationPool_.GetComponentArray<Position>("Position");

      for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
      {
        float xOffset = rng.RangeFloat(-data_.xVariance_, data_.xVariance_);
        float yOffset = rng.RangeFloat(-data_.yVariance_, data_.yVariance_);

        for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned destIndex = CalculateDestinationIndex(info, object, group, layerCopy);
            Position& destPosition = destPositions.Data(destIndex);

            destPosition.x_ += xOffset;
            destPosition.y_ += yOffset;
          }
        }
      }
    }
  }
}