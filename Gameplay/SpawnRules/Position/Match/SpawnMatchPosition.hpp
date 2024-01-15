/* ======================================================================== */
/*!
 * \file            SpawnMatchPosition.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnMatchPosition_BARRAGE_H
#define SpawnMatchPosition_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    class MatchPosition : public SpawnRule
    {
      public:
        MatchPosition();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnMatchPosition_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////