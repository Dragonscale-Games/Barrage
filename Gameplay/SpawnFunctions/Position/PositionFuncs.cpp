/* ======================================================================== */
/*!
 * \file            PositionFuncs.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Spawn functions that set the initial position of an object.
 */
 /* ======================================================================== */

#include "PositionFuncs.hpp"
#include <Engine/Engine.hpp>

using namespace Barrage;

namespace Barrage
{
  namespace Spawn
  {
    void MatchPosition(Pool& initPool, Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, const std::vector<unsigned>& sourceIndices)
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
  }
}