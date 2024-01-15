/* ======================================================================== */
/*!
 * \file            SpawnOffsetLocal.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnOffsetLocal_BARRAGE_H
#define SpawnOffsetLocal_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    class OffsetLocal : public SpawnRule
    {
    public:
      OffsetLocal();

      std::shared_ptr<SpawnRule> Clone() const override;

      void Execute(SpawnRuleInfo& info) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnOffsetLocal_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////