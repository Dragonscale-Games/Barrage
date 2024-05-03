/* ======================================================================== */
/*!
 * \file            SpawnAdjustSpeed.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnAdjustSpeed.hpp"
#include "Objects/Pools/Pool.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"

namespace Barrage
{
  namespace Spawn
  {
    AdjustSpeed::AdjustSpeed() : SpawnRuleT<AdjustSpeedData>("AdjustSpeed") {}

    std::shared_ptr<SpawnRule> AdjustSpeed::Clone() const
    {
      return std::make_shared<AdjustSpeed>(*this);
    }

    void AdjustSpeed::Execute(SpawnRuleInfo& info)
    {
      VelocityArray& destVelocities = info.destinationPool_.GetComponentArray<Velocity>("Velocity");

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          float speed = data_.base_ + static_cast<float>(group) * data_.delta_;

          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned destIndex = CalculateDestinationIndex(info, object, group, layerCopy);
            Velocity& velocity = destVelocities.Data(destIndex);

            velocity.AddSpeed(speed);
          }
        }
      }
    }

    void AdjustSpeed::Reflect()
    {
      rttr::registration::class_<Spawn::AdjustSpeedData>("AdjustSpeedData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("base", &Spawn::AdjustSpeedData::base_)
        .property("delta", &Spawn::AdjustSpeedData::delta_)
        ;
    }
  }
}