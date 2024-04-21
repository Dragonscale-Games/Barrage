/* ======================================================================== */
/*!
 * \file            SpawnAdjustDirection.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Applies a constant direction to a spawned object.

   Requirements:
   - Velocity (destination)
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnAdjustDirection_BARRAGE_H
#define SpawnAdjustDirection_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct AdjustDirectionData
    {
      Radian angle_;

      inline AdjustDirectionData() : angle_(0.0f) {};
    };

    class AdjustDirection : public SpawnRuleT<AdjustDirectionData>
    {
    public:
      AdjustDirection();

      std::shared_ptr<SpawnRule> Clone() const override;

      void Execute(SpawnRuleInfo& info) override;

      static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnAdjustDirection_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////