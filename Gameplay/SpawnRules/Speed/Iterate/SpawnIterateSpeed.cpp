
/* ======================================================================== */
/*!
 * \file            SpawnIterateSpeed.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnIterateSpeed.hpp"
#include "Objects/Pools/Pool.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  namespace Spawn
  {
    IterateSpeed::IterateSpeed() : SpawnRuleTA<IterateSpeedData, IterateSpeedArrayElement>("IterateSpeed") {}

    std::shared_ptr<SpawnRule> IterateSpeed::Clone() const
    {
      return std::make_shared<IterateSpeed>(*this);
    }

    void IterateSpeed::Execute(SpawnRuleInfo& info)
    {
      float& speed = dataArray_.Data(info.sourceIndex_).speed_;
      VelocityArray& destVelocities = info.destinationPool_.GetComponentArray<Velocity>("Velocity");

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned destIndex = CalculateDestinationIndex(info, object, group, layerCopy);
            Velocity& destVelocity = destVelocities.Data(destIndex);

            destVelocity.AddSpeed(speed);
          }
        }
      }

      speed += data_.speedStep_;
    }

    void IterateSpeed::Reflect()
    {
      rttr::registration::class_<Spawn::IterateSpeedData>("IterateSpeedData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("speedStep", &Spawn::IterateSpeedData::speedStep_)
        ;
    }
  }
}