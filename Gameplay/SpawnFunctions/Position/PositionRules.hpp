/* ======================================================================== */
/*!
 * \file            PositionRules.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Spawn rules that set the initial position of an object.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef PositionRules_BARRAGE_H
#define PositionRules_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Objects/Spawning/SpawnRule.hpp>

namespace Barrage
{
  namespace Spawn
  {
    class MatchPosition : public SpawnRule
    {
      public:
        MatchPosition();
        
        void Execute(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // PositionRules_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////