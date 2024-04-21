/* ======================================================================== */
/*!
 * \file            SpawnIterateCount.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Applies a random direction to a spawned object.

   Requirements:
   -Velocity (destination)
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnIterateCount_BARRAGE_H
#define SpawnIterateCount_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct IterateCountData
    {
      int countStep_;
      unsigned min_;
      unsigned max_;

      inline IterateCountData() : countStep_(1), min_(0), max_(100) {};
    };
    
    class IterateCount : public SpawnRuleT<IterateCountData>
    {
      public:
        IterateCount();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        void SetRTTRValue(const rttr::variant& value) override;

        SpawnRuleStage GetStage() override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnIterateCount_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////