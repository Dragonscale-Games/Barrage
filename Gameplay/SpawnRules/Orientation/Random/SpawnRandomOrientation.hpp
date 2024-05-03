/* ======================================================================== */
/*!
 * \file            SpawnRandomOrientation.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Applies a random orientation to an entire layer of objects.

   Requirements:
   -Position (destination)
   -Velocity (destination)
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnRandomOrientation_BARRAGE_H
#define SpawnRandomOrientation_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    class RandomOrientation : public SpawnRule
    {
      public:
        RandomOrientation();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnRandomOrientation_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////