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

#include <rttr/registration.h>
#include <rttr/constructor.h>
#include <Objects/Components/EngineComponents.hpp>
#include <Objects/Archetypes/PoolArchetype/PoolArchetype.hpp>

namespace Barrage
{
  void ReflectBarrageCore()
  {
    // Shared Components.

    // Circle Collider
    rttr::registration::class_<CircleCollider>("CircleCollider")
      .property("radius", &CircleCollider::radius_)
      /*
      .constructor<>(
        rttr::policy::ctor::as_object
      )
      */;
    // Box Collider
    rttr::registration::class_<BoundaryBox>("BoundaryBox")
      .property("xMin", &BoundaryBox::xMin_)
      .property("yMin", &BoundaryBox::yMin_)
      .property("xMax", &BoundaryBox::xMax_)
      .property("yMax", &BoundaryBox::yMax_)
      /*.constructor<>(
        rttr::policy::ctor::as_object
      )*/;
    // Spawn Type
    rttr::registration::class_<SpawnType>("SpawnType")
      .property("archetypeName", &SpawnType::archetypeName_)
      .property("destinationPoolName", &SpawnType::destinationPoolName_)
      .property("destinationPoolCapacity", &SpawnType::destinationPoolCapacity_)
      .property("spawnFuncs", &SpawnType::spawnFuncs_)
      /*.constructor<>(
        rttr::policy::ctor::as_object
      )*/;
    // Spawner
    rttr::registration::class_<Spawner>("Spawner")
      .property("spawnTypes", &Spawner::spawnTypes_)
      /*.constructor<>(
        rttr::policy::ctor::as_object
      )*/;
    // Sprite
    rttr::registration::class_<Sprite>("Sprite")
      .property("texture", &Sprite::texture_)
      .property("layer", &Sprite::layer_)
      /*.constructor<>(
        rttr::policy::ctor::as_object
      )*/;
    // Random
    /*
    rttr::registration::class_<Random>("Random")
      .property_readonly("startSeed", &Random::GetSeed(), rttr::access_levels::public_access);
    */

    // Component Arrays.

    // Angular Speed.
    rttr::registration::class_<AngularSpeed>("AngularSpeed")
      .property("w", &AngularSpeed::w_)
      /*.constructor<>(
        rttr::policy::ctor::as_object
      )*/;
    // Destructible Arrays.
    rttr::registration::class_<Destructible>("Destructible")
      .property("destroyed", &Destructible::destroyed_)
      /*.constructor<>(
        rttr::policy::ctor::as_object
      )*/;
    // Lifetime Arrays.
    rttr::registration::class_<Lifetime>("Lifetime")
      .property("ticks", &Lifetime::ticks_)
      /*.constructor<>(
        rttr::policy::ctor::as_object
      )*/;
    // Position Arrays.
    rttr::registration::class_<Position>("Position")
      .property("x", &Position::x_)
      .property("y", &Position::y_)
      /*.constructor<>(
        rttr::policy::ctor::as_object
      )*/;
    // Scale Arrays.
    rttr::registration::class_<Scale>("Scale")
      .property("x", &Position::x_)
      .property("y", &Position::y_)
      /*.constructor<>(
        rttr::policy::ctor::as_object
      )*/;
    // Rotation Arrays.
    rttr::registration::class_<Rotation>("Rotation")
      .property("angle", &Rotation::angle_)
      /*.constructor<>(
        rttr::policy::ctor::as_object
      )*/;
  }
}
