/* ======================================================================== */
/*!
 * \file            MatchControlPoints.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef MatchControlPoints_BARRAGE_H
#define MatchControlPoints_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    class MatchControlPoints : public SpawnRule
    {
      public:
        MatchControlPoints();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;
    };

    class MatchPathing : public SpawnRule
    {
      public:
        MatchPathing();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // MatchControlPoints_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////