/* ======================================================================== */
/*!
 * \file            SpawnRandomCircleOffset.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnRandomCircleOffset_BARRAGE_H
#define SpawnRandomCircleOffset_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    class RandomCircleOffset : public SpawnRule
    {
    public:
      RandomCircleOffset();

      std::shared_ptr<SpawnRule> Clone() const override;

      void Execute(SpawnRuleInfo& info) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnRandomCircleOffset_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////