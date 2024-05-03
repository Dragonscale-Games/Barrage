/* ======================================================================== */
/*!
 * \file            SpawnIterateDirection.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnIterateDirection_BARRAGE_H
#define SpawnIterateDirection_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct IterateDirectionData
    {
      Radian angleStep_;

      inline IterateDirectionData() : angleStep_(0.0f) {};
    };

    struct IterateDirectionArrayElement
    {
      Radian angle_;

      inline IterateDirectionArrayElement() : angle_(0.0f) {};
    };

    class IterateDirection : public SpawnRuleTA<IterateDirectionData, IterateDirectionArrayElement>
    {
    public:
      IterateDirection();

      std::shared_ptr<SpawnRule> Clone() const override;

      void Execute(SpawnRuleInfo& info) override;

      static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnIterateDirection_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////