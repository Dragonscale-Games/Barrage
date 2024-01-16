 
/* ======================================================================== */
/*!
 * \file            SpawnRandomBoxOffset.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnRandomBoxOffset.hpp"
#include "Spaces/Space.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"
#include "Objects/Pools/Pool.hpp"

namespace Barrage
{
  namespace Spawn
  {
    RandomBoxOffset::RandomBoxOffset() : SpawnRuleT<RandomBoxOffsetData>("RandomBoxOffset") {}

    std::shared_ptr<SpawnRule> RandomBoxOffset::Clone() const
    {
      return std::make_shared<RandomBoxOffset>(*this);
    }

    void RandomBoxOffset::Execute(SpawnRuleInfo& info)
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

    void RandomBoxOffset::Reflect()
    {
      rttr::registration::class_<Spawn::RandomBoxOffsetData>("RandomBoxOffset")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("xVariance", &Spawn::RandomBoxOffsetData::xVariance_)
        .property("yVariance", &Spawn::RandomBoxOffsetData::yVariance_)
        ;
    }
  }
}