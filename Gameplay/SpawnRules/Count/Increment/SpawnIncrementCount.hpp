/* ======================================================================== */
/*!
 * \file            SpawnIncrementCount.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Applies a random direction to a spawned object.

   Requirements:
   -Velocity (destination)
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnIncrementCount_BARRAGE_H
#define SpawnIncrementCount_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct IncrementCountData
    {
      int amount_;

      inline IncrementCountData() : amount_(0) {};
    };
    
    class IncrementCount : public SpawnRuleT<IncrementCountData>
    {
      public:
        IncrementCount();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        SpawnRuleStage GetStage() override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnIncrementCount_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////