/* ======================================================================== */
/*!
 * \file            SpawnAdjustRotation.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnAdjustRotation_BARRAGE_H
#define SpawnAdjustRotation_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct AdjustRotationData
    {
      Radian angle_;

      inline AdjustRotationData() : angle_(0.0f) {};
    };

    class AdjustRotation : public SpawnRuleT<AdjustRotationData>
    {
      public:
        AdjustRotation();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnAdjustRotation_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////