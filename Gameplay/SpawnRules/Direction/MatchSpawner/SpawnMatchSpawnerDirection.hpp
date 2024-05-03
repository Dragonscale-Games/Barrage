/* ======================================================================== */
/*!
 * \file            SpawnMatchSpawnerDirection.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnMatchSpawnerDirection_BARRAGE_H
#define SpawnMatchSpawnerDirection_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    class MatchSpawnerDirection : public SpawnRule
    {
    public:
      MatchSpawnerDirection();

      std::shared_ptr<SpawnRule> Clone() const override;

      void Execute(SpawnRuleInfo& info) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnMatchSpawnerDirection_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////