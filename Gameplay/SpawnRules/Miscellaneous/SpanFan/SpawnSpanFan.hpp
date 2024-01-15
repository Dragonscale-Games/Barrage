/* ======================================================================== */
/*!
 * \file            SpawnSpanFan.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnSpanFan_BARRAGE_H
#define SpawnSpanFan_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    class SpanFan : public SpawnRule
    {
    public:
      SpanFan();

      std::shared_ptr<SpawnRule> Clone() const override;

      void Execute(SpawnRuleInfo& info) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnSpanFan_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////