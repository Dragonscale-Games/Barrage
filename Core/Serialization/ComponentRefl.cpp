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
    // Shared Components.
    
    // Spawn Type
    rttr::registration::class_<SpawnType>("SpawnType")
      .property("archetypeName", &SpawnType::archetypeName_)
      .property("destinationPoolName", &SpawnType::destinationPoolName_)
      .property("spawnFuncs", &SpawnType::spawnFuncs_);

    // Spawner
    rttr::registration::class_<Spawner>("Spawner")
      .property("spawnTypes", &Spawner::spawnTypes_);
    rttr::type::get<Spawner*>();

    // Sprite
    rttr::registration::class_<Sprite>("Sprite")
      .property("texture", &Sprite::texture_)
      .property("layer", &Sprite::layer_);
    rttr::type::get<Sprite*>();

    // Component Arrays.

    // Destructible Arrays.
    rttr::registration::class_<DestructibleArray>("DestructibleArray")
      .property("Destructible", &DestructibleArray::data_);
    rttr::type::get<DestructibleArray*>();
    rttr::registration::class_<Destructible>("Destructible");

    // Position Arrays.
    rttr::registration::class_<PositionArray>("PositionArray")
      .property("Position", &PositionArray::data_);
    rttr::type::get<PositionArray*>();
    rttr::registration::class_<Position>("Position")
      .property("x", &Position::x_)
      .property("y", &Position::y_);

    // Scale Arrays.
    rttr::registration::class_<ScaleArray>("ScaleArray")
      .property("Scale", &ScaleArray::data_);
    rttr::type::get<ScaleArray*>();
    rttr::registration::class_<Scale>("Scale")
      .property("w", &Scale::w_)
      .property("h", &Scale::h_);

    // Rotation Arrays.
    rttr::registration::class_<RotationArray>("RotationArray")
      .property("Rotation", &RotationArray::data_);
    rttr::type::get<RotationArray*>();
    rttr::registration::class_<Rotation>("Rotation")
      .property("angle", &Rotation::angle_);
  }
}
