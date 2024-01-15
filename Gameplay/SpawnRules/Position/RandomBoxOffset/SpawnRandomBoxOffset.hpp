/* ======================================================================== */
/*!
 * \file            SpawnRandomBoxOffset.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnRandomBoxOffset_BARRAGE_H
#define SpawnRandomBoxOffset_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct RandomBoxOffsetData
    {
      float xVariance_;
      float yVariance_;

      inline RandomBoxOffsetData() : xVariance_(0.0f), yVariance_(0.0f) {};
    };
    
    class RandomBoxOffset : public SpawnRuleT<RandomBoxOffsetData>
    {
      public:
        RandomBoxOffset();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnRandomBoxOffset_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////