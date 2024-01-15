/* ======================================================================== */
/*!
 * \file            SpawnOffsetGlobal.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnOffsetGlobal_BARRAGE_H
#define SpawnOffsetGlobal_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"
#include "glm/glm.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct OffsetGlobalData
    {
      glm::vec2 base_;
      glm::vec2 delta_;

      inline OffsetGlobalData() : base_(0.0f), delta_(0.0f) {};
    };
    
    class OffsetGlobal : public SpawnRuleT<OffsetGlobalData>
    {
      public:
        OffsetGlobal();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnOffsetGlobal_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////