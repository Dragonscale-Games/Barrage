/* ======================================================================== */
/*!
 * \file            SpawnSetRotation.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Applies a constant direction to a spawned object.

   Requirements:
   - Velocity (destination)
 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnSetRotation.hpp"
#include "Objects/Pools/Pool.hpp"
#include "ComponentArrays/Rotation/RotationArray.hpp"

namespace Barrage
{
  namespace Spawn
  {
    SetRotation::SetRotation() : SpawnRuleT<SetRotationData>("SetRotation") {}

    std::shared_ptr<SpawnRule> SetRotation::Clone() const
    {
      return std::make_shared<SetRotation>(*this);
    }

    void SetRotation::Execute(SpawnRuleInfo& info)
    {
      RotationArray& destRotations = info.destinationPool_.GetComponentArray<Rotation>("Rotation");

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned destIndex = CalculateDestinationIndex(info, object, group, layerCopy);
            Rotation& destRotation = destRotations.Data(destIndex);

            destRotation.angle_.value_ = data_.angle_.value_;
          }
        }
      }
    }

    void SetRotation::Reflect()
    {
      rttr::registration::class_<Spawn::SetRotationData>("SetRotationData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("angle", &Spawn::SetRotationData::angle_)
        ;
    }
  }
}