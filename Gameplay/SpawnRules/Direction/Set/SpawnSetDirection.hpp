/* ======================================================================== */
/*!
 * \file            SpawnSetDirection.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Applies a constant direction to a spawned object.

   Requirements:
   - Velocity (destination)
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnSetDirection_BARRAGE_H
#define SpawnSetDirection_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct SetDirectionData
    {
      Radian angle_;

      inline SetDirectionData() : angle_(0.0f) {};
    };
    
    class SetDirection : public SpawnRuleT<SetDirectionData>
    {
      public:
        SetDirection();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnSetDirection_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////