/* ======================================================================== */
/*!
 * \file            SpawnMirror.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnMirror_BARRAGE_H
#define SpawnMirror_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    class Mirror : public SpawnRule
    {
      public:
        Mirror();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnMirror_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////