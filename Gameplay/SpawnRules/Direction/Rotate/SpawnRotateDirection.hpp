/* ======================================================================== */
/*!
 * \file            SpawnRotateDirection.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Applies a rotation to a spawned object's direction.

   Requirements:
   - Velocity (destination)
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnRotateDirection_BARRAGE_H
#define SpawnRotateDirection_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct RotateDirectionData
    {
      Radian angle_;
      float cosineAngle_; // precomputed, should not be edited manually
      float sinAngle_;    // precomputed, should not be edited manually

      inline RotateDirectionData() : angle_(0.0f), cosineAngle_(1.0f), sinAngle_(0.0f) {};
    };
    
    class RotateDirection : public SpawnRuleT<RotateDirectionData>
    {
      public:
        RotateDirection();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        void SetRTTRValue(const rttr::variant& value) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnRotateDirection_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////