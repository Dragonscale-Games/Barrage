/* ======================================================================== */
/*!
 * \file            SpawnRandomPositionBox.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnRandomPositionBox_BARRAGE_H
#define SpawnRandomPositionBox_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct RandomPositionBoxData
    {
      float xVariance_;
      float yVariance_;

      inline RandomPositionBoxData() : xVariance_(0.0f), yVariance_(0.0f) {};
    };
    
    class RandomPositionBox : public SpawnRuleT<RandomPositionBoxData>
    {
      public:
        RandomPositionBox();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnRandomPositionBox_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////