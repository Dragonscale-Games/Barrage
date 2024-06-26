/* ======================================================================== */
/*!
 * \file            SpawnSetSpeed.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:
   - Velocity (destination)
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnSetSpeed_BARRAGE_H
#define SpawnSetSpeed_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct SetSpeedData
    {
      float baseSpeed_;
      float delta_;

      inline SetSpeedData() : baseSpeed_(0.0f), delta_(0.0f) {};
    };
    
    class SetSpeed : public SpawnRuleT<SetSpeedData>
    {
      public:
        SetSpeed();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnSetSpeed_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////