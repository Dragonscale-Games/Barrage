/* ======================================================================== */
/*!
 * \file            SpawnSetColor.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Sets the color tint of an object.

   Requirements:
   -ColorTint (destination)
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnSetColor_BARRAGE_H
#define SpawnSetColor_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Spawning/SpawnRule.hpp"
#include "ComponentArrays/ColorTint/ColorTintArray.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct SetColorData
    {
      ColorTint color_;

      inline SetColorData() : color_() {};
    };

    class SetColor : public SpawnRuleT<SetColorData>
    {
      public:
        SetColor();

        std::shared_ptr<SpawnRule> Clone() const override;

        void Execute(SpawnRuleInfo& info) override;

        SpawnRuleStage GetStage() override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnSetColor_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////