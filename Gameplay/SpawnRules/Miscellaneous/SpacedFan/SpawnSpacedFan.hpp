/* ======================================================================== */
/*!
 * \file            SpawnSpacedFan.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnSpacedFan_BARRAGE_H
#define SpawnSpacedFan_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    class SpacedFan : public SpawnRule
    {
    public:
      SpacedFan();

      std::shared_ptr<SpawnRule> Clone() const override;

      void Execute(SpawnRuleInfo& info) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnSpacedFan_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////