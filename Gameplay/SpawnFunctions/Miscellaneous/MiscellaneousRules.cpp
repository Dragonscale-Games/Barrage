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

        Pool::DuplicationResult duplicationResult = destPool.DuplicateObject(numRingObjects - 1, destIndex, sourceIndex, sourceIndices);

        Position& destPosition = destPositions.Data(destIndex);
        Velocity& destVelocity = destVelocities.Data(destIndex);

        glm::vec2 direction(destVelocity.vx_, destVelocity.vy_);
        float speed = glm::length(direction);
        float initialTheta = glm::atan(direction.y, direction.x);
        Position origin(destPosition);

        SetPositionAndVelocity(destPosition, destVelocity, origin, initialTheta, speed, radius);

        for (unsigned j = 0; j < duplicationResult.numDuplicates_; ++j)
        {
          unsigned dupIndex = duplicationResult.firstIndex_ + j;

          Position& dupPosition = destPositions.Data(dupIndex);
          Velocity& dupVelocity = destVelocities.Data(dupIndex);

          float theta = angleStep * (j + 1) + initialTheta;

          SetPositionAndVelocity(dupPosition, dupVelocity, origin, theta, speed, radius);
        }
      }
    }

    glm::vec2 SpawnRing::CalculatePositionVector(float radius, float theta)
    {
      float cosTheta = glm::cos(theta);
      float sinTheta = glm::sin(theta);

      return glm::vec2(radius * cosTheta, radius * sinTheta);
    }

    glm::vec2 SpawnRing::CalculateVelocityVector(float speed, glm::vec2 positionVector)
    {
      return speed * glm::normalize(positionVector);
    }

    void SpawnRing::SetPositionAndVelocity(Position& position, Velocity& velocity, const Position& origin, float theta, float speed, float radius)
    {
      glm::vec2 positionVector = CalculatePositionVector(radius, theta);
      glm::vec2 velocityVector = CalculateVelocityVector(speed, positionVector);

      position.x_ = origin.x_ + positionVector.x;
      position.y_ = origin.y_ + positionVector.y;

      velocity.vx_ = velocityVector.x;
      velocity.vy_ = velocityVector.y;
    }
  }
}