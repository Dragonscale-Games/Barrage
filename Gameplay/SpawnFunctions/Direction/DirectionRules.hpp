/* ======================================================================== */
/*!
 * \file            DirectionRules.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Spawn functions that set the initial direction of an object's velocity.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef DirectionRules_BARRAGE_H
#define DirectionRules_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Objects/Spawning/SpawnRule.hpp>

namespace Barrage
{
  namespace Spawn
  {
    class RandomDirection : public SpawnRule
    {
      public:
        RandomDirection();
        
        void Execute(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // DirectionRules_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////