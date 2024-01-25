
/* ======================================================================== */
/*!
 * \file            MatchControlPoints.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "MatchControlPoints.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"
#include "Objects/Pools/Pool.hpp"
#include "Components/Movement/Movement.hpp"

namespace Barrage
{
  namespace Spawn
  {
    MatchControlPoints::MatchControlPoints() : SpawnRule("MatchControlPoints") {}

    std::shared_ptr<SpawnRule> MatchControlPoints::Clone() const
    {
      return std::make_shared<MatchControlPoints>(*this);
    }

    void MatchControlPoints::Execute(SpawnRuleInfo& info)
    {
      Movement& movement = info.sourcePool_.GetComponent<Movement>("Movement").Data();
      PositionArray& destPositions = info.destinationPool_.GetComponentArray<Position>("Position");

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          Position controlPosition;

          switch (group % 4)
          {
            case 0:
              controlPosition = movement.curve_.GetP0();
              break;
             
            case 1:
              controlPosition = movement.curve_.GetP1();
              break;

            case 2:
              controlPosition = movement.curve_.GetP2();
              break;

            case 3:
              controlPosition = movement.curve_.GetP3();
              break;
          }
          
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned destIndex = CalculateDestinationIndex(info, object, group, layerCopy);
            Position& destPosition = destPositions.Data(destIndex);

            destPosition = controlPosition;
          }
        }
      }
    }

    MatchPathing::MatchPathing() : SpawnRule("MatchPathing") {}

    std::shared_ptr<SpawnRule> MatchPathing::Clone() const
    {
      return std::make_shared<MatchPathing>(*this);
    }

    void MatchPathing::Execute(SpawnRuleInfo& info)
    {
      Movement& movement = info.sourcePool_.GetComponent<Movement>("Movement").Data();
      PositionArray& destPositions = info.destinationPool_.GetComponentArray<Position>("Position");

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          double step = 1.0 / info.groupInfo_.numGroups_;
          Position pathPosition = movement.curve_.GetPosition(group * step);

          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned destIndex = CalculateDestinationIndex(info, object, group, layerCopy);
            Position& destPosition = destPositions.Data(destIndex);

            destPosition = pathPosition;
          }
        }
      }
    }
  }
}