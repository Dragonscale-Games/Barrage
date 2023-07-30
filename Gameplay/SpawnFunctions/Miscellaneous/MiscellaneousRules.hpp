/* ======================================================================== */
/*!
 * \file            MiscellaneousRules.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Miscellaneous spawn rules that don't fit clearly anywhere else.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef MiscellaneousRules_BARRAGE_H
#define MiscellaneousRules_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Objects/Spawning/SpawnFunctionManager.hpp>

namespace Barrage
{
  namespace Spawn
  {
    void SpawnRing(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices);
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // MiscellaneousRules_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////