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

    void SpawnRing::SetPositionAndVelocity(Position& position, Velocity& velocity, const Position& origin, float theta, float speed, float radius)
    {
      float cosTheta = glm::cos(theta);
      float sinTheta = glm::sin(theta);
      
      glm::vec2 positionVector = glm::vec2(radius * cosTheta, radius * sinTheta);
      glm::vec2 velocityVector = speed * glm::vec2(cosTheta, sinTheta);

      position.x_ = origin.x_ + positionVector.x;
      position.y_ = origin.y_ + positionVector.y;

      velocity.vx_ = velocityVector.x;
      velocity.vy_ = velocityVector.y;
    }

    MirrorAcrossAxis::MirrorAcrossAxis() : SpawnRuleT<MirrorAcrossAxisData>("MirrorAcrossAxis") {}

    void MirrorAcrossAxis::Execute(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices)
    {
      PositionArray& sourcePositions = *initPool.GetComponentArray<Position>("Position");
      PositionArray& destPositions = *destPool.GetComponentArray<Position>("Position");
      VelocityArray& destVelocities = *destPool.GetComponentArray<Velocity>("Velocity");
      
      glm::mat2 inverseRotationMatrix = glm::transpose(data_.rotationMatrix_);

      for (unsigned i = 0; i < numNewObjects; ++i)
      {
        unsigned destIndex = firstObjIndex + i;
        unsigned sourceIndex = sourceIndices[i];

        Pool::DuplicationResult duplicationResult = destPool.DuplicateObject(1, destIndex, sourceIndex, sourceIndices);

        if (duplicationResult.numDuplicates_)
        {
          Position& sourcePosition = sourcePositions.Data(sourceIndex);
          Position& dupPosition = destPositions.Data(duplicationResult.firstIndex_);
          Velocity& dupVelocity = destVelocities.Data(duplicationResult.firstIndex_);

          glm::vec2 positionTemp(dupPosition.x_ - sourcePosition.x_, dupPosition.y_ - sourcePosition.y_);
          positionTemp = data_.rotationMatrix_ * positionTemp;
          positionTemp.y = -positionTemp.y;
          positionTemp = inverseRotationMatrix * positionTemp;

          dupPosition.x_ = positionTemp.x + sourcePosition.x_;
          dupPosition.y_ = positionTemp.y + sourcePosition.y_;

          glm::vec2 velocityTemp(dupVelocity.vx_, dupVelocity.vy_);
          velocityTemp = data_.rotationMatrix_ * velocityTemp;
          velocityTemp.y = -velocityTemp.y;
          velocityTemp = inverseRotationMatrix * velocityTemp;

          dupVelocity.vx_ = velocityTemp.x;
          dupVelocity.vy_ = velocityTemp.y;
        }
      }
    }

    void MirrorAcrossAxis::SetRTTRValue(const rttr::variant& value)
    {
      SpawnRuleT<MirrorAcrossAxisData>::SetRTTRValue(value);

      float cosAngle = glm::cos(data_.angle_.value_);
      float sinAngle = glm::sin(data_.angle_.value_);
      
      data_.rotationMatrix_ = glm::mat2(cosAngle, -sinAngle, sinAngle, cosAngle);
    }
  }
}