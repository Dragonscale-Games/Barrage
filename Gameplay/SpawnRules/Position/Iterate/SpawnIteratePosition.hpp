/* ======================================================================== */
/*!
 * \file            SpawnIteratePosition.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnIteratePosition_BARRAGE_H
#define SpawnIteratePosition_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"
#include "Utilities/Utilities.hpp"
#include <glm/glm.hpp>

namespace Barrage
{
  namespace Spawn
  {
    struct IteratePositionData
    {
      glm::vec2 positionStep_;

      inline IteratePositionData() : positionStep_(0.0f, 0.0f) {};
    };

    struct IteratePositionArrayElement
    {
      glm::vec2 offset_;

      inline IteratePositionArrayElement() : offset_(0.0f) {};
    };

    class IteratePosition : public SpawnRuleTA<IteratePositionData, IteratePositionArrayElement>
    {
    public:
      IteratePosition();

      std::shared_ptr<SpawnRule> Clone() const override;

      void Execute(SpawnRuleInfo& info) override;

      static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnIteratePosition_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////