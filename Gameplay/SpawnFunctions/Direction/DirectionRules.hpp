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

#include <Objects/Spawning/SpawnRule.hpp>

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
      float angle_;
      float cosineAngle_; // precomputed, should not be edited manually
      float sinAngle_;    // precomputed, should not be edited manually

      inline RotateDirectionData() : angle_(0.0f), cosineAngle_(0.0f), sinAngle_(0.0f) {};
    };

    class RotateDirection : public SpawnRuleT<RotateDirectionData>
    {
      public:
        RotateDirection();

        void Execute(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices) override;

        virtual void SetRTTRValue(const rttr::variant& value) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // DirectionRules_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////