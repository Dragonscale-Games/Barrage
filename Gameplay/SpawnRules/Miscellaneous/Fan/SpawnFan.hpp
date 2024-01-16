/* ======================================================================== */
/*!
 * \file            SpawnFan.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnFan_BARRAGE_H
#define SpawnFan_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct FanData
    {
      Radian spacing_;

      inline FanData() : spacing_(0.0f) {};
    };
    
    class Fan : public SpawnRuleT<FanData>
    {
      public:
        Fan();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnFan_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////