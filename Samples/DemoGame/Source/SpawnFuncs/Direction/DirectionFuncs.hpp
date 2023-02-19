/* ======================================================================== */
/*!
 * \file            DirectionFuncs.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Spawn functions that set the initial direction of an object's velocity.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef DirectionFuncs_BARRAGE_H
#define DirectionFuncs_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Objects/SpawnFunctions/SpawnFunctionManager.hpp>

namespace Demo
{
  namespace Spawn 
  {
    void RandomDirection(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, const std::vector<unsigned>& sourceIndices);
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // DirectionFuncs_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////