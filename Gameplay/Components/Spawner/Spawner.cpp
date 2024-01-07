/* ======================================================================== */
/*!
 * \file            STUBMODULE.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   
 */
 /* ======================================================================== */

#include "Spawner.hpp"

namespace Barrage
{
  AutomaticSpawn::AutomaticSpawn() :
    spawnType_(),
    ticksPerSpawn_(0),
    delay_(0)
  {
  }


  SpawnPattern::SpawnPattern() :
    automaticSpawns_()
  {
  }

  Spawner::Spawner() : 
    currentPattern_(), 
    patterns_(), 
    spawnTypes_()
  {
  }

  void Spawner::Reflect()
  {
    rttr::registration::class_<SpawnLayer>("SpawnLayer")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("numGroups", &SpawnLayer::baseNumGroups_)
      ;
    
    rttr::registration::class_<SpawnType>("SpawnType")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("spawnLayers", &SpawnType::spawnLayers_)
      .property("destinationPool", &SpawnType::destinationPool_)
      .property("spawnArchetype", &SpawnType::spawnArchetype_)
      ;

    rttr::registration::class_<AutomaticSpawn>("AutomaticSpawn")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("spawnType", &AutomaticSpawn::spawnType_)
      .property("ticksPerSpawn", &AutomaticSpawn::ticksPerSpawn_)
      .property("delay", &AutomaticSpawn::delay_)
      ;
    
    rttr::registration::class_<SpawnPattern>("SpawnPattern")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("automaticSpawns", &SpawnPattern::automaticSpawns_)
      ;
    
    rttr::registration::class_<Spawner>("Spawner")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("currentPattern", &Spawner::currentPattern_)
      .property("patterns", &Spawner::patterns_)
      .property("spawnTypes", &Spawner::spawnTypes_)
      ;
  }
}