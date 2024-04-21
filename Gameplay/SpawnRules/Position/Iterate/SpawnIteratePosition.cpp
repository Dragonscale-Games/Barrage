
/* ======================================================================== */
/*!
 * \file            SpawnIteratePosition.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnIteratePosition.hpp"
#include "Objects/Pools/Pool.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  namespace Spawn
  {
    IteratePosition::IteratePosition() : SpawnRuleTA<IteratePositionData, IteratePositionArrayElement>("IteratePosition") {}

    std::shared_ptr<SpawnRule> IteratePosition::Clone() const
    {
      return std::make_shared<IteratePosition>(*this);
    }

    void IteratePosition::Execute(SpawnRuleInfo& info)
    {
      glm::vec2& offset = dataArray_.Data(info.sourceIndex_).offset_;
      
      PositionArray& destPositions = info.destinationPool_.GetComponentArray<Position>("Position");

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned destIndex = CalculateDestinationIndex(info, object, group, layerCopy);
            Position& destPosition = destPositions.Data(destIndex);

            destPosition.x_ += offset.x;
            destPosition.y_ += offset.y;
          }
        }
      }

      offset += data_.positionStep_;
    }

    void IteratePosition::Reflect()
    {
      rttr::registration::class_<Spawn::IteratePositionData>("IteratePositionData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("positionStep", &Spawn::IteratePositionData::positionStep_)
        ;
    }
  }
}