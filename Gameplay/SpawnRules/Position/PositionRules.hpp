/* ======================================================================== */
/*!
 * \file            PositionRules.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Spawn rules that set the initial position of an object.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef PositionRules_BARRAGE_H
#define PositionRules_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Objects/Spawning/SpawnRule.hpp>

namespace Barrage
{
  namespace Spawn
  {
    class MatchPosition : public SpawnRule
    {
      public:
        MatchPosition();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;
    };

    struct RandomOffsetData
    {
      float xVariance_;
      float yVariance_;

      inline RandomOffsetData() : xVariance_(0.0f), yVariance_(0.0f) {};
    };

    class RandomOffset : public SpawnRuleT<RandomOffsetData>
    {
      public:
        RandomOffset();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // PositionRules_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////