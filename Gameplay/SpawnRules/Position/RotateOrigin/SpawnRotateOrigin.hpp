/* ======================================================================== */
/*!
 * \file            SpawnRotateOrigin.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnRotateOrigin_BARRAGE_H
#define SpawnRotateOrigin_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    class RotateOrigin : public SpawnRule
    {
    public:
      RotateOrigin();

      std::shared_ptr<SpawnRule> Clone() const override;

      void Execute(SpawnRuleInfo& info) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnRotateOrigin_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////