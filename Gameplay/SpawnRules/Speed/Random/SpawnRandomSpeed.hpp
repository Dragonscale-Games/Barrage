/* ======================================================================== */
/*!
 * \file            SpawnRandomSpeed.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnRandomSpeed_BARRAGE_H
#define SpawnRandomSpeed_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct RandomSpeedData
    {
      float minSpeed_;
      float maxSpeed_;

      inline RandomSpeedData() : minSpeed_(0.0f), maxSpeed_(1.0f) {};
    };
    
    class RandomSpeed : public SpawnRuleT<RandomSpeedData>
    {
      public:
        RandomSpeed();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        void SetRTTRValue(const rttr::variant& value) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnRandomSpeed_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////