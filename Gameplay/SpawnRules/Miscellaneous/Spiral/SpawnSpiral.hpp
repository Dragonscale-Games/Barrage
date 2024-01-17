/* ======================================================================== */
/*!
 * \file            SpawnSpiral.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnSpiral_BARRAGE_H
#define SpawnSpiral_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct SpiralData
    {
      Radian angleDelta_;

      inline SpiralData() : angleDelta_(0.0f) {};
    };

    struct SpiralArrayElement
    {
      Radian angle_;

      inline SpiralArrayElement() : angle_(0.0f) {};
    };
    
    class Spiral : public SpawnRuleTA<SpiralData, SpiralArrayElement>
    {
      public:
        Spiral();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnSpiral_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////