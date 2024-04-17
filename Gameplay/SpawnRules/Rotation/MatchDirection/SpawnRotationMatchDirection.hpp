/* ======================================================================== */
/*!
 * \file            SpawnRotationMatchDirection.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnRotationMatchDirection_BARRAGE_H
#define SpawnRotationMatchDirection_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    class RotationMatchDirection : public SpawnRule
    {
      public:
        RotationMatchDirection();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnRotationMatchDirection_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////