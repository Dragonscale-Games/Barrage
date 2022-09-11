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

namespace Barrage
{
  namespace Spawn
  {
    void MatchPosition(Pool& initPool, Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, const std::vector<unsigned>& sourceIndices)
    {
      PositionArray& source_positions = *initPool.GetComponentArray<PositionArray>("PositionArray");
      PositionArray& dest_positions = *destPool.GetComponentArray<PositionArray>("PositionArray");

      for (unsigned i = 0; i < numNewObjects; ++i)
      {
        unsigned source_index = sourceIndices[i];

        dest_positions[i + firstObjIndex].x_ = source_positions[source_index].x_;
        dest_positions[i + firstObjIndex].y_ = source_positions[source_index].y_;
      }
    }
  }
}