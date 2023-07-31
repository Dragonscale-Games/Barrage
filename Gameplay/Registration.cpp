/* ======================================================================== */
/*!
 * \file            Registration.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Gameplay code registration.
 */
 /* ======================================================================== */

#include <Objects/ObjectManager.hpp>

#include <Entry/Entry.hpp>

#include "ComponentArrays/AngularSpeedArray.hpp"
#include "ComponentArrays/DestructibleArray.hpp"
#include "ComponentArrays/PositionArray.hpp"
#include "ComponentArrays/RotationArray.hpp"
#include "ComponentArrays/ScaleArray.hpp"
#include "ComponentArrays/SpawnTimerArray.hpp"
#include "ComponentArrays/VelocityArray.hpp"

#include "Components/BoundaryBox.hpp"
#include "Components/CircleCollider.hpp"
#include "Components/Player.hpp"
#include "Components/Spawner.hpp"
#include "Components/Sprite.hpp"

#include "Systems/Creation/CreationSystem.hpp"
#include "Systems/Destruction/DestructionSystem.hpp"
#include "Systems/Collision/CollisionSystem.hpp"
#include "Systems/Movement/MovementSystem.hpp"
#include "Systems/Spawn/SpawnSystem.hpp"

#include "SpawnFunctions/Direction/DirectionRules.hpp"
#include "SpawnFunctions/Miscellaneous/MiscellaneousRules.hpp"
#include "SpawnFunctions/Position/PositionRules.hpp"

namespace Barrage
{
  void ReflectBarrageCore()
  {
    rttr::registration::class_<Entry::SpaceEntry>("SpaceEntry")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("Name", &Entry::SpaceEntry::name_)
      .property("Scene", &Entry::SpaceEntry::scene_)
      ;
    
    rttr::registration::class_<Entry>("Entry")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("Spaces", &Entry::spaces_)
      .property("Textures", &Entry::textures_)
      ;
    
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
      .property("spawnRules", &SpawnInfo::spawnRuleNames_)
      ;

    rttr::registration::class_<Spawner>("Spawner")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("currentPattern", &Spawner::currentPattern_)
      .property("patterns", &Spawner::patterns_)
      .property("spawnTypes", &Spawner::spawnTypes_)
      ;

    rttr::registration::class_<Position>("Position")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("x", &Position::x_)
      .property("y", &Position::y_)
      ;

    rttr::registration::class_<Rotation>("Rotation")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("angle", &Rotation::angle_)
      ;

    rttr::registration::class_<Scale>("Scale")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("w", &Scale::w_)
      .property("h", &Scale::h_)
      ;

    rttr::registration::class_<Scale>("Scale")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("w", &Scale::w_)
      .property("h", &Scale::h_)
      ;

    rttr::registration::class_<Velocity>("Velocity")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("vx", &Velocity::vx_)
      .property("vy", &Velocity::vy_)
      ;
  }
  
  void ObjectManager::RegisterCustomComponents()
  {
    RegisterComponentArray<AngularSpeed>("AngularSpeed");
    RegisterComponentArray<Destructible>("Destructible");
    RegisterComponentArray<Position>("Position");
    RegisterComponentArray<Rotation>("Rotation");
    RegisterComponentArray<Scale>("Scale");
    RegisterComponentArray<SpawnTimer>("SpawnTimer");
    RegisterComponentArray<Velocity>("Velocity");

    RegisterComponent<BoundaryBox>("BoundaryBox");
    RegisterComponent<CircleCollider>("CircleCollider");
    RegisterComponent<Player>("Player");
    RegisterComponent<Spawner>("Spawner");
    RegisterComponent<Sprite>("Sprite");

    ComponentAllocator::RegisterTag("Bullet");
  }

  void ObjectManager::RegisterCustomSystems()
  {
    RegisterSystem<CollisionSystem>("CollisionSystem");
    RegisterSystem<CreationSystem>("CreationSystem");
    RegisterSystem<DestructionSystem>("DestructionSystem");
    // Draw system is registered by engine
    RegisterSystem<MovementSystem>("MovementSystem");
    RegisterSystem<SpawnSystem>("SpawnSystem");
  }

  void ObjectManager::RegisterCustomSpawnFunctions()
  {
    RegisterSpawnRule<Spawn::MatchPosition>("MatchPosition");
    RegisterSpawnRule<Spawn::RandomDirection>("RandomDirection");
    RegisterSpawnRule<Spawn::SpawnRing>("SpawnRing");
  }

  void ObjectManager::SetSystemUpdateOrder()
  {
    std::vector<std::string_view> update_order;

    update_order.push_back("CreationSystem");
    update_order.push_back("DestructionSystem");
    update_order.push_back("MovementSystem");
    update_order.push_back("SpawnSystem");
    update_order.push_back("CreationSystem");
    update_order.push_back("CollisionSystem");

    SetSystemUpdateOrder(update_order);
  }
}