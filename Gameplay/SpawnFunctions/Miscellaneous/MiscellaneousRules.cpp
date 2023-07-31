/* ======================================================================== */
/*!
 * \file            MiscellaneousRules.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Miscellaneous spawn rules that don't fit clearly anywhere else.
 */
 /* ======================================================================== */

#include "MiscellaneousRules.hpp"
#include <Engine/Engine.hpp>
#include "ComponentArrays/PositionArray.hpp"
#include "ComponentArrays/VelocityArray.hpp"
#include <glm/glm.hpp>

using namespace Barrage;

namespace Barrage
{
  namespace Spawn
  {
    SpawnRing::SpawnRing() : SpawnRuleT<SpawnRingData>("SpawnRing") {}
    
    void SpawnRing::Execute(Pool& initPool, Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices)
    {
      unsigned numRingObjects = data_.numObjects_;
      float radius = data_.radius_;
      float angleStep = 2.0f * 3.1415926f / numRingObjects;

      PositionArray& destPositions = *destPool.GetComponentArray<Position>("Position");
      VelocityArray& destVelocities = *destPool.GetComponentArray<Velocity>("Velocity");

      for (unsigned i = 0; i < numNewObjects; ++i)
      {
        unsigned destIndex = firstObjIndex + i;
        unsigned sourceIndex = sourceIndices[i];

        Position& destPosition = destPositions.Data(destIndex);
        Velocity& destVelocity = destVelocities.Data(destIndex);

        glm::vec2 direction(destVelocity.vx_, destVelocity.vy_);
        float speed = glm::length(direction);
        direction = glm::normalize(direction);
        
        float initialTheta = glm::atan(direction.y, direction.x);

        Position origin(destPosition);

        destPosition.x_ += radius * direction.x;
        destPosition.y_ += radius * direction.y;
        
        Pool::DuplicationResult duplicationResult = destPool.DuplicateObject(numRingObjects - 1, destIndex, sourceIndex, sourceIndices);

        if (duplicationResult.numDuplicates_ == 0)
        {
          break;
        }

        for (unsigned j = 0; j < duplicationResult.numDuplicates_; ++j)
        {
          unsigned dupIndex = duplicationResult.firstIndex_ + j;

          Position& dupPosition = destPositions.Data(dupIndex);
          Velocity& dupVelocity = destVelocities.Data(dupIndex);

          float theta = angleStep * (j + 1) + initialTheta;
          float cosTheta = glm::cos(theta);
          float sinTheta = glm::sin(theta);

          glm::vec2 positionVector(radius * cosTheta, radius * sinTheta);

          dupPosition.x_ = origin.x_ + positionVector.x;
          dupPosition.y_ = origin.y_ + positionVector.y;

          glm::vec2 velocityVector = speed * glm::normalize(positionVector);

          dupVelocity.vx_ = velocityVector.x;
          dupVelocity.vy_ = velocityVector.y;
        }
      }
    }
  }
}