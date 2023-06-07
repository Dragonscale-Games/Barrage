/* ========================================================================= */
/*!
 *
 * \file            ComponentRefl.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * Provides the reflection data for components in Barrage.
 */
 /* ========================================================================= */

//  ===========================================================================
// Includes
//  ===========================================================================

#include <string>
#include <rttr/registration.h>
#include <rttr/constructor.h>
#include <Objects/Components/EngineComponents.hpp>
#include <Objects/Archetypes/PoolArchetype/PoolArchetype.hpp>
#include <Utilities/Utilities.hpp>

namespace Barrage
{
  void ReflectBarrageCore()
  { 

    // Sprite
    rttr::registration::class_<Sprite>("Sprite")
      .property("texture", &Sprite::texture_)
      .property("layer", &Sprite::layer_)
    ;

    // Destructible Arrays.
    rttr::registration::class_<Destructible>("Destructible");

    // Position Arrays.
    rttr::registration::class_<Position>("Position")
      .property("x", &Position::x_)
      .property("y", &Position::y_)
    ;

    // Scale Arrays.
    rttr::registration::class_<Scale>("Scale")
      .property("w", &Scale::w_)
      .property("h", &Scale::h_)
    ;

    // Rotation Arrays.
    rttr::registration::class_<Rotation>("Rotation")
      .property("angle", &Rotation::angle_)
    ;
  }
}
