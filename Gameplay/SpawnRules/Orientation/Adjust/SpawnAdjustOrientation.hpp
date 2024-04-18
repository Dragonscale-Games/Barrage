/* ======================================================================== */
/*!
 * \file            SpawnAdjustOrientation.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Rotates the orientation of an entire layer of objects.

   Requirements:
   - Position (destination)
   - Velocity (destination)
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnAdjustOrientation_BARRAGE_H
#define SpawnAdjustOrientation_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct AdjustOrientationData
    {
      Radian angle_;
      float cosineAngle_; // precomputed, should not be edited manually
      float sinAngle_;    // precomputed, should not be edited manually

      inline AdjustOrientationData() : angle_(0.0f), cosineAngle_(1.0f), sinAngle_(0.0f) {};
    };

    class AdjustOrientation : public SpawnRuleT<AdjustOrientationData>
    {
      public:
        AdjustOrientation();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        void SetRTTRValue(const rttr::variant& value) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnAdjustOrientation_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////