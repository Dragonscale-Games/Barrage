/* ======================================================================== */
/*!
 * \file            SpawnIncrementSpeed.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnIncrementSpeed_BARRAGE_H
#define SpawnIncrementSpeed_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct IncrementSpeedData
    {
      float base_;
      float delta_;

      inline IncrementSpeedData() : base_(MINIMUM_SPEED), delta_(0.0f) {};
    };
    
    class IncrementSpeed : public SpawnRuleT<IncrementSpeedData>
    {
      public:
        IncrementSpeed();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnIncrementSpeed_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////