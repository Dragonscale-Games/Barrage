/* ======================================================================== */
/*!
 * \file            RttrComponents.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   RTTR registration for components.
 */
 /* ======================================================================== */

#include <string>
#include <rttr/registration.h>

#include "Components/BoundaryBox.hpp"
#include "Components/CircleCollider.hpp"
#include "Components/Player.hpp"
#include "Components/Spawner.hpp"
#include "Components/Sprite.hpp"

namespace Barrage
{
  void ReflectComponents()
  {
    rttr::registration::class_<BoundaryBox>("BoundaryBox")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("xMin", &BoundaryBox::xMin_)
      .property("xMax", &BoundaryBox::xMax_)
      .property("yMin", &BoundaryBox::yMin_)
      .property("yMax", &BoundaryBox::yMax_)
      ;

    rttr::registration::class_<CircleCollider>("CircleCollider")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("radius", &CircleCollider::radius_)
      ;

    rttr::registration::class_<Player>("Player")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("speedFast", &Player::speedFast_)
      .property("speedSlow", &Player::speedSlow_)
      ;

    rttr::registration::class_<Sprite>("Sprite")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("texture", &Sprite::texture_)
      .property("layer", &Sprite::layer_)
      ;

    rttr::registration::class_<SpawnTypeList>("SpawnTypeList")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("spawnTypes", &SpawnTypeList::spawnTypes_)
      ;

    rttr::registration::class_<AutomaticSpawn>("AutomaticSpawn")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("spawnType", &AutomaticSpawn::spawnType_)
      .property("ticksPerSpawn", &AutomaticSpawn::ticksPerSpawn_)
      .property("numberPerBurst", &AutomaticSpawn::numberPerBurst_)
      .property("delay", &AutomaticSpawn::delay_)
      ;

    rttr::registration::class_<SpawnPattern>("SpawnPattern")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("spawnSequence", &SpawnPattern::spawnSequence_)
      .property("automaticSpawns", &SpawnPattern::automaticSpawns_)
      ;

    rttr::registration::class_<SpawnInfo>("SpawnInfo")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("destinationPool", &SpawnInfo::destinationPoolName_)
      .property("spawnArchetype", &SpawnInfo::spawnArchetypeName_)
      .property("spawnRules", &SpawnInfo::spawnRules_)
      ;

    rttr::registration::class_<Spawner>("Spawner")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("currentPattern", &Spawner::currentPattern_)
      .property("patterns", &Spawner::patterns_)
      .property("spawnTypes", &Spawner::spawnTypes_)
      ;
  }
}