/* ======================================================================== */
/*!
 * \file            SpawnAdjustSpeed.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnAdjustSpeed_BARRAGE_H
#define SpawnAdjustSpeed_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct AdjustSpeedData
    {
      float base_;
      float delta_;

      inline AdjustSpeedData() : base_(0.0f), delta_(0.0f) {};
    };

    class AdjustSpeed : public SpawnRuleT<AdjustSpeedData>
    {
      public:
        AdjustSpeed();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnAdjustSpeed_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////