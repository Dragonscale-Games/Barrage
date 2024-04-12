/* ======================================================================== */
/*!
 * \file            SpawnAimedDirection.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnAimedDirection_BARRAGE_H
#define SpawnAimedDirection_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    class AimedDirection : public SpawnRule
    {
      public:
        AimedDirection();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnAimedDirection_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////