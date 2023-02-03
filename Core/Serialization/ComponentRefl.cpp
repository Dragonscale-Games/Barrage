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

namespace Barrage
{
  void ReflectBarrageCore()
  {
    // Shared Components.

    // Spawn Type
    rttr::registration::class_<SpawnType>("SpawnType")
      .property("archetypeName", &SpawnType::archetypeName_)
      .property("destinationPoolName", &SpawnType::destinationPoolName_)
      .property("spawnFuncs", &SpawnType::spawnFuncs_);

    // Spawner
    rttr::registration::class_<Spawner>("Spawner")
      .property("spawnTypes", &Spawner::spawnTypes_);

    // Sprite
    rttr::registration::class_<Sprite>("Sprite")
      .property("texture", &Sprite::texture_)
      .property("layer", &Sprite::layer_);

    // Component Arrays.

    // Destructible Arrays.
    rttr::registration::class_<Destructible>("Destructible")
      .property("destroyed", &Destructible::destroyed_);

    // Position Arrays.
    rttr::registration::class_<Position>("Position")
      .property("x", &Position::x_)
      .property("y", &Position::y_);

    // Scale Arrays.
    rttr::registration::class_<Scale>("Scale")
      .property("x", &Position::x_)
      .property("y", &Position::y_);

    // Rotation Arrays.
    rttr::registration::class_<Rotation>("Rotation")
      .property("angle", &Rotation::angle_);
  }
}
