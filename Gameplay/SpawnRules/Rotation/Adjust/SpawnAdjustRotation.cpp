
/* ======================================================================== */
/*!
 * \file            SpawnAdjustRotation.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

   Requirements:
   -Velocity (destination)
 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnAdjustRotation.hpp"
#include "Objects/Pools/Pool.hpp"
#include "ComponentArrays/Rotation/RotationArray.hpp"

namespace Barrage
{
  namespace Spawn
  {
    AdjustRotation::AdjustRotation() : SpawnRuleT<AdjustRotationData>("AdjustRotation") {}

    std::shared_ptr<SpawnRule> AdjustRotation::Clone() const
    {
      return std::make_shared<AdjustRotation>(*this);
    }

    void AdjustRotation::Execute(SpawnRuleInfo& info)
    {
      RotationArray& destRotations = info.destinationPool_.GetComponentArray<Rotation>("Rotation");

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned dest_index = CalculateDestinationIndex(info, object, group, layerCopy);
            Rotation& destRotation = destRotations.Data(dest_index);

            destRotation.angle_.value_ = ClampWrapped(destRotation.angle_.value_ + data_.angle_.value_, 0.0f, 2.0f * BARRAGE_PI);
          }
        }
      }
    }

    void AdjustRotation::Reflect()
    {
      rttr::registration::class_<Spawn::AdjustRotationData>("AdjustRotationData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("angle", &Spawn::AdjustRotationData::angle_)
        ;
    }
  }
}