/* ======================================================================== */
/*!
 * \file            DirectionFuncs.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Spawn functions that set the initial direction of an object's velocity.
 */
 /* ======================================================================== */

#include "DirectionFuncs.hpp"
#include <Engine/Engine.hpp>
#include <stdafx.h>

#include "ComponentArrays/VelocityArray.hpp"

namespace Barrage
{
  namespace Spawn
  {
    void RandomDirection(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices)
    {
      UNREFERENCED(sourceIndices);
      
      Barrage::Random& rng = initPool.GetSpace().GetRNG();
      VelocityArray& dest_velocities = *destPool.GetComponentArray<Velocity>("Velocity");

      for (unsigned i = 0; i < numNewObjects; ++i)
      {
        unsigned dest_index = i + firstObjIndex;
        float angle = 3.141592f * rng.RangeFloat(0, 2.0f);
        
        dest_velocities.Data(dest_index).vx_ = cos(angle);
        dest_velocities.Data(dest_index).vy_ = sin(angle);
      }
    }
  }
}