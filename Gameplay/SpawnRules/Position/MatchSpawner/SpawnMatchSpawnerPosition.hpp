/* ======================================================================== */
/*!
 * \file            SpawnMatchSpawnerPosition.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnMatchSpawnerPosition_BARRAGE_H
#define SpawnMatchSpawnerPosition_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    class MatchSpawnerPosition : public SpawnRule
    {
      public:
        MatchSpawnerPosition();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnMatchSpawnerPosition_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////