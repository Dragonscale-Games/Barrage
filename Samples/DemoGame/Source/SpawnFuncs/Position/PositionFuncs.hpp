/* ======================================================================== */
/*!
 * \file            PositionFuncs.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Spawn functions that set the initial position of an object.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef PositionFuncs_BARRAGE_H
#define PositionFuncs_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Objects/SpawnFuncs/SpawnFuncManager.hpp>

namespace Demo
{
  namespace Spawn
  {
    void MatchPosition(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, const std::vector<unsigned>& sourceIndices);
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // PositionFuncs_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////