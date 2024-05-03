/* ======================================================================== */
/*!
 * \file            SpawnSetRotation.hpp
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
#ifndef SpawnSetRotation_BARRAGE_H
#define SpawnSetRotation_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct SetRotationData
    {
      Radian angle_;

      inline SetRotationData() : angle_(0.0f) {};
    };

    class SetRotation : public SpawnRuleT<SetRotationData>
    {
      public:
        SetRotation();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnSetRotation_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////