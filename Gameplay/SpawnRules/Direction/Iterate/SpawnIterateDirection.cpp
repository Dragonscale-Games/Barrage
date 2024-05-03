
/* ======================================================================== */
/*!
 * \file            SpawnIterateDirection.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnIterateDirection.hpp"
#include "Objects/Pools/Pool.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  namespace Spawn
  {
    IterateDirection::IterateDirection() : SpawnRuleTA<IterateDirectionData, IterateDirectionArrayElement>("IterateDirection") {}

    std::shared_ptr<SpawnRule> IterateDirection::Clone() const
    {
      return std::make_shared<IterateDirection>(*this);
    }

    void IterateDirection::Execute(SpawnRuleInfo& info)
    {
      float& angle = dataArray_.Data(info.sourceIndex_).angle_.value_;

      VelocityArray& dest_velocities = info.destinationPool_.GetComponentArray<Velocity>("Velocity");

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned dest_index = CalculateDestinationIndex(info, object, group, layerCopy);
            Velocity& dest_velocity = dest_velocities.Data(dest_index);

            dest_velocity.Rotate(angle);
          }
        }
      }

      angle = ClampWrapped(angle + data_.angleStep_.value_, 0.0f, 2.0f * BARRAGE_PI);
    }

    void IterateDirection::Reflect()
    {
      rttr::registration::class_<Spawn::IterateDirectionData>("IterateDirectionData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("angleStep", &Spawn::IterateDirectionData::angleStep_)
        ;
    }
  }
}