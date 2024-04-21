/* ======================================================================== */
/*!
 * \file            SpawnRandomRotation.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnRandomRotation.hpp"
#include "Random/Random.hpp"
#include "ComponentArrays/Rotation/RotationArray.hpp"
#include "Spaces/Space.hpp"

namespace Barrage
{
  namespace Spawn
  {
    RandomRotation::RandomRotation() : SpawnRule("RandomRotation") {}

    std::shared_ptr<SpawnRule> RandomRotation::Clone() const
    {
      return std::make_shared<RandomRotation>(*this);
    }

    void RandomRotation::Execute(SpawnRuleInfo& info)
    {
      Random& rng = info.space_.RNG();
      RotationArray& destRotations = info.destinationPool_.GetComponentArray<Rotation>("Rotation");

      for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
      {
        float angle = rng.RangeFloat(0, 2.0f * BARRAGE_PI);

        for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned destIndex = CalculateDestinationIndex(info, object, group, layerCopy);
            Rotation& destRotation = destRotations.Data(destIndex);

            destRotation.angle_ = angle;
          }
        }
      }
    }
  }
}