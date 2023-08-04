/* ======================================================================== */
/*!
 * \file            PositionRules.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Spawn rules that set the initial position of an object.
 */
 /* ======================================================================== */

#include "PositionRules.hpp"
#include <Engine/Engine.hpp>
#include "ComponentArrays/PositionArray.hpp"

namespace Barrage
{
  namespace Spawn
  {
    MatchPosition::MatchPosition() : SpawnRule("MatchPosition") {}
    
    void MatchPosition::Execute(Pool& initPool, Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices)
    {
      PositionArray& source_positions = *initPool.GetComponentArray<Position>("Position");
      PositionArray& dest_positions = *destPool.GetComponentArray<Position>("Position");

      for (unsigned i = 0; i < numNewObjects; ++i)
      {
        unsigned dest_index = i + firstObjIndex;
        unsigned source_index = sourceIndices[i];

        dest_positions.Data(dest_index).x_ = source_positions.Data(source_index).x_;
        dest_positions.Data(dest_index).y_ = source_positions.Data(source_index).y_;
      }
    }

    Offset::Offset() : SpawnRuleT<OffsetData>("Offset") {}

    void Offset::Execute(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices)
    {
      PositionArray& dest_positions = *destPool.GetComponentArray<Position>("Position");

      for (unsigned i = 0; i < numNewObjects; ++i)
      {
        unsigned dest_index = i + firstObjIndex;

        dest_positions.Data(dest_index).x_ += data_.xOffset_;
        dest_positions.Data(dest_index).y_ += data_.yOffset_;
      }
    }

    RandomOffset::RandomOffset() : SpawnRuleT<RandomOffsetData>("RandomOffset") {}

    void RandomOffset::Execute(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices)
    {
      Barrage::Random& rng = destPool.GetSpace().GetRNG();
      PositionArray& dest_positions = *destPool.GetComponentArray<Position>("Position");

      for (unsigned i = 0; i < numNewObjects; ++i)
      {
        unsigned dest_index = i + firstObjIndex;

        dest_positions.Data(dest_index).x_ += rng.RangeFloat(-data_.xVariance_, data_.xVariance_);
        dest_positions.Data(dest_index).y_ += rng.RangeFloat(-data_.yVariance_, data_.yVariance_);
      }
    }
  }
}