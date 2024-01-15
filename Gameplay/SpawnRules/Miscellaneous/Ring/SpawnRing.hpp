/* ======================================================================== */
/*!
 * \file            SpawnRing.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnRing_BARRAGE_H
#define SpawnRing_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    class Ring : public SpawnRule
    {
    public:
      Ring();

      std::shared_ptr<SpawnRule> Clone() const override;

      void Execute(SpawnRuleInfo& info) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnRing_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////