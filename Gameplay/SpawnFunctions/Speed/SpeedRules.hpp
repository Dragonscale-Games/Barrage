/* ======================================================================== */
/*!
 * \file            SpeedRules.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Spawn rules that set the initial speed of an object.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpeedRules_BARRAGE_H
#define SpeedRules_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Objects/Spawning/SpawnRule.hpp>

namespace Barrage
{
  namespace Spawn
  {
    struct RandomSpeedData
    {
      float minSpeed_;
      float maxSpeed_;

      inline RandomSpeedData() : minSpeed_(0.0f), maxSpeed_(0.0f) {};
    };
    
    class RandomSpeed : public SpawnRuleT<RandomSpeedData>
    {
      public:
        RandomSpeed();

        void Execute(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices) override;

        virtual void SetRTTRValue(const rttr::variant& value) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpeedRules_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////