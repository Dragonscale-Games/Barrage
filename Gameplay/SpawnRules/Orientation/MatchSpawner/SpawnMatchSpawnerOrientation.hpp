/* ======================================================================== */
/*!
 * \file            SpawnMatchSpawnerOrientation.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnMatchSpawnerOrientation_BARRAGE_H
#define SpawnMatchSpawnerOrientation_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    class MatchSpawnerOrientation : public SpawnRule
    {
      public:
        MatchSpawnerOrientation();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnMatchSpawnerOrientation_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////