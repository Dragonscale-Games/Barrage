/* ======================================================================== */
/*!
 * \file            SpawnAdjustPosition.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnAdjustPosition_BARRAGE_H
#define SpawnAdjustPosition_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"
#include "glm/glm.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct AdjustPositionData
    {
      glm::vec2 base_;
      glm::vec2 delta_;

      inline AdjustPositionData() : base_(0.0f), delta_(0.0f) {};
    };
    
    class AdjustPosition : public SpawnRuleT<AdjustPositionData>
    {
      public:
        AdjustPosition();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnAdjustPosition_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////