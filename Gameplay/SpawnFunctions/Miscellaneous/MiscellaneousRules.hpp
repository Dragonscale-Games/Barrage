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

#include <Objects/Spawning/SpawnRule.hpp>

namespace Barrage
{
  namespace Spawn
  {
    struct SpawnRingData
    {
      unsigned numObjects_;
      float radius_;

      inline SpawnRingData() : numObjects_(10), radius_(100.0f) {};
    };
    
    class SpawnRing : public SpawnRuleT<SpawnRingData>
    {
      public:
        SpawnRing();
        
        void Execute(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // MiscellaneousRules_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////