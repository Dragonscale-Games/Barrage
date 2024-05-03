 
/* ======================================================================== */
/*!
 * \file            SpawnRandomPositionBox.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnRandomPositionBox.hpp"
#include "Spaces/Space.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"
#include "Objects/Pools/Pool.hpp"

namespace Barrage
{
  namespace Spawn
  {
    RandomPositionBox::RandomPositionBox() : SpawnRuleT<RandomPositionBoxData>("RandomPositionBox") {}

    std::shared_ptr<SpawnRule> RandomPositionBox::Clone() const
    {
      return std::make_shared<RandomPositionBox>(*this);
    }

    void RandomPositionBox::Execute(SpawnRuleInfo& info)
    {
      Random& rng = info.space_.RNG();
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

    void RandomPositionBox::Reflect()
    {
      rttr::registration::class_<Spawn::RandomPositionBoxData>("RandomPositionBox")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("xVariance", &Spawn::RandomPositionBoxData::xVariance_)
        .property("yVariance", &Spawn::RandomPositionBoxData::yVariance_)
        ;
    }
  }
}