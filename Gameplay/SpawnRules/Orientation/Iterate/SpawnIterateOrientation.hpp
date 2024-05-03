/* ======================================================================== */
/*!
 * \file            SpawnIterateOrientation.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnIterateOrientation_BARRAGE_H
#define SpawnIterateOrientation_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct IterateOrientationData
    {
      Radian angleStep_;

      inline IterateOrientationData() : angleStep_(0.0f) {};
    };

    struct IterateOrientationArrayElement
    {
      Radian angle_;

      inline IterateOrientationArrayElement() : angle_(0.0f) {};
    };
    
    class IterateOrientation : public SpawnRuleTA<IterateOrientationData, IterateOrientationArrayElement>
    {
      public:
        IterateOrientation();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnIterateOrientation_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////