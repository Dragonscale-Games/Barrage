/* ======================================================================== */
/*!
 * \file            SpawnSetPosition.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnSetPosition_BARRAGE_H
#define SpawnSetPosition_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"
#include "glm/glm.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct SetPositionData
    {
      glm::vec2 position_;

      inline SetPositionData() : position_(0.0f) {};
    };

    class SetPosition : public SpawnRuleT<SetPositionData>
    {
      public:
        SetPosition();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnSetPosition_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////