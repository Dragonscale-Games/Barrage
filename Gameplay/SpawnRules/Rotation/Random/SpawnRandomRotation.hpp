/* ======================================================================== */
/*!
 * \file            SpawnRandomRotation.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnRandomRotation_BARRAGE_H
#define SpawnRandomRotation_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    class RandomRotation : public SpawnRule
    {
      public:
        RandomRotation();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnRandomRotation_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////