/* ======================================================================== */
/*!
 * \file            SpawnOffsetPosition.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnOffsetPosition_BARRAGE_H
#define SpawnOffsetPosition_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"
#include "glm/glm.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct OffsetPositionData
    {
      glm::vec2 base_;
      glm::vec2 delta_;

      inline OffsetPositionData() : base_(0.0f), delta_(0.0f) {};
    };
    
    class OffsetPosition : public SpawnRuleT<OffsetPositionData>
    {
      public:
        OffsetPosition();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnOffsetPosition_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////