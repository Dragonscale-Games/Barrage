/* ======================================================================== */
/*!
 * \file            SpawnRandomDirection.hpp
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
#ifndef SpawnRandomDirection_BARRAGE_H
#define SpawnRandomDirection_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    class RandomDirection : public SpawnRule
    {
      public:
        RandomDirection();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnRandomDirection_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////