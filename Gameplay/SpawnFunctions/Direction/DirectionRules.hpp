/* ======================================================================== */
/*!
 * \file            DirectionRules.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Spawn functions that set the initial direction of an object's velocity.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef DirectionRules_BARRAGE_H
#define DirectionRules_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  namespace Spawn
  {
    class RandomDirection : public SpawnRule
    {
      public:
        RandomDirection();
        
        void Execute(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices) override;
    };

    struct RotateDirectionData
    {
      RADIAN angle_;
      float cosineAngle_; // precomputed, should not be edited manually
      float sinAngle_;    // precomputed, should not be edited manually

      inline RotateDirectionData() : angle_(0.0f), cosineAngle_(1.0f), sinAngle_(0.0f) {};
    };

    class RotateDirection : public SpawnRuleT<RotateDirectionData>
    {
      public:
        RotateDirection();

        void Execute(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices) override;

        void SetRTTRValue(const rttr::variant& value) override;
    };

    struct SetDirectionData
    {
      RADIAN angle_;
      float xDirection_;
      float yDirection_;

      inline SetDirectionData() : angle_(0.0f), xDirection_(1.0f), yDirection_(0.0f) {};
    };

    class SetDirection : public SpawnRuleT<SetDirectionData>
    {
      public:
        SetDirection();

        void Execute(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices) override;

        void SetRTTRValue(const rttr::variant& value) override;
    };

    struct SpiralData
    {
      RADIAN angleDelta_;

      inline SpiralData() : angleDelta_(0.0f) {};
    };

    struct SpiralArrayElement
    {
      RADIAN angle_;

      inline SpiralArrayElement() : angle_(0.0f) {};
    };

    class Spiral : public SpawnRuleTA<SpiralData, SpiralArrayElement>
    {
      public:
        Spiral();

        void Execute(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // DirectionRules_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////