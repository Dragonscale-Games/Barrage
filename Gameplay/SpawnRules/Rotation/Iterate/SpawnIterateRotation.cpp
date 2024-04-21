
/* ======================================================================== */
/*!
 * \file            SpawnIterateRotation.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnIterateRotation.hpp"
#include "Objects/Pools/Pool.hpp"
#include "ComponentArrays/Rotation/RotationArray.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  namespace Spawn
  {
    IterateRotation::IterateRotation() : SpawnRuleTA<IterateRotationData, IterateRotationArrayElement>("IterateRotation") {}

    std::shared_ptr<SpawnRule> IterateRotation::Clone() const
    {
      return std::make_shared<IterateRotation>(*this);
    }

    void IterateRotation::Execute(SpawnRuleInfo& info)
    {
      float& angle = dataArray_.Data(info.sourceIndex_).angle_.value_;
      RotationArray& destRotations = info.destinationPool_.GetComponentArray<Rotation>("Rotation");

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned destIndex = CalculateDestinationIndex(info, object, group, layerCopy);
            Rotation& destRotation = destRotations.Data(destIndex);

            destRotation.angle_.value_ += angle;
          }
        }
      }

      angle = ClampWrapped(angle + data_.angleStep_.value_, 0.0f, 2.0f * BARRAGE_PI);
    }

    void IterateRotation::Reflect()
    {
      rttr::registration::class_<Spawn::IterateRotationData>("IterateRotationData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("angleStep", &Spawn::IterateRotationData::angleStep_)
        ;
    }
  }
}