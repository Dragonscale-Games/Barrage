/* ======================================================================== */
/*!
 * \file            SpawnIterateRotation.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnIterateRotation_BARRAGE_H
#define SpawnIterateRotation_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct IterateRotationData
    {
      Radian angleStep_;

      inline IterateRotationData() : angleStep_(0.0f) {};
    };

    struct IterateRotationArrayElement
    {
      Radian angle_;

      inline IterateRotationArrayElement() : angle_(0.0f) {};
    };

    class IterateRotation : public SpawnRuleTA<IterateRotationData, IterateRotationArrayElement>
    {
    public:
      IterateRotation();

      std::shared_ptr<SpawnRule> Clone() const override;

      void Execute(SpawnRuleInfo& info) override;

      static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnIterateRotation_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////