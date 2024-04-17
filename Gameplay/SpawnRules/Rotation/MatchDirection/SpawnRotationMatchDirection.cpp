
/* ======================================================================== */
/*!
 * \file            SpawnRotationMatchDirection.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnRotationMatchDirection.hpp"
#include "ComponentArrays/Rotation/RotationArray.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"
#include "Objects/Pools/Pool.hpp"
#include <glm/glm.hpp>

namespace Barrage
{
  namespace Spawn
  {
    RotationMatchDirection::RotationMatchDirection() : SpawnRule("RotationMatchDirection") {}

    std::shared_ptr<SpawnRule> RotationMatchDirection::Clone() const
    {
      return std::make_shared<RotationMatchDirection>(*this);
    }

    void RotationMatchDirection::Execute(SpawnRuleInfo& info)
    {
      RotationArray& destRotations = info.destinationPool_.GetComponentArray<Rotation>("Rotation");
      VelocityArray& destVelocities = info.destinationPool_.GetComponentArray<Velocity>("Velocity");

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned destIndex = CalculateDestinationIndex(info, object, group, layerCopy);
            Rotation& destRotation = destRotations.Data(destIndex);
            Velocity& destVelocity = destVelocities.Data(destIndex);
            
            destRotation.angle_ = glm::atan(-destVelocity.vx_, destVelocity.vy_);
          }
        }
      }
    }
  }
}