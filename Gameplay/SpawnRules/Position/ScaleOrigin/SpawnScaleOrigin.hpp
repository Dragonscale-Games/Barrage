/* ======================================================================== */
/*!
 * \file            SpawnScaleOrigin.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnScaleOrigin_BARRAGE_H
#define SpawnScaleOrigin_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    class ScaleOrigin : public SpawnRule
    {
    public:
      ScaleOrigin();

      std::shared_ptr<SpawnRule> Clone() const override;

      void Execute(SpawnRuleInfo& info) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnScaleOrigin_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////