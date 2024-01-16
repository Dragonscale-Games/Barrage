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
      float cosineAngle_; // precomputed, should not be edited manually
      float sinAngle_;    // precomputed, should not be edited manually

      inline SetDirectionData() : angle_(0.0f), cosineAngle_(1.0f), sinAngle_(0.0f) {};
    };
    
    class SetDirection : public SpawnRuleT<SetDirectionData>
    {
      public:
        SetDirection();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        void SetRTTRValue(const rttr::variant& value) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnSetDirection_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////