/* ======================================================================== */
/*!
 * \file            SpawnIterateSpeed.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnIterateSpeed_BARRAGE_H
#define SpawnIterateSpeed_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"
#include "Utilities/Utilities.hpp"
#include <glm/glm.hpp>

namespace Barrage
{
  namespace Spawn
  {
    struct IterateSpeedData
    {
      float speedStep_;

      inline IterateSpeedData() : speedStep_(0.0f) {};
    };

    struct IterateSpeedArrayElement
    {
      float speed_;

      inline IterateSpeedArrayElement() : speed_(0.0f) {};
    };

    class IterateSpeed : public SpawnRuleTA<IterateSpeedData, IterateSpeedArrayElement>
    {
      public:
        IterateSpeed();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnIterateSpeed_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////