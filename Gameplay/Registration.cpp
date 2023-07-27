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
#include "ComponentArrays/VelocityArray.hpp"
#include "ComponentArrays/DestructibleArray.hpp"
#include "ComponentArrays/PositionArray.hpp"
#include "ComponentArrays/RotationArray.hpp"
#include "ComponentArrays/ScaleArray.hpp"

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

#include "SpawnFunctions/Direction/DirectionFuncs.hpp"
#include "SpawnFunctions/Position/PositionFuncs.hpp"

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

    rttr::registration::class_<Spawner>("Spawner")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("spawnTypes", &Spawner::spawnTypes_)
      .property("testMap", &Spawner::testMap_)
      ;

    rttr::registration::class_<SpawnInfo>("SpawnInfo")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("archetypeName", &SpawnInfo::archetypeName_)
      .property("spawnFunctions", &SpawnInfo::spawnFunctions_)
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

    rttr::registration::class_<AngularSpeed>("AngularSpeed")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("w", &AngularSpeed::w_)
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
    RegisterComponentArray<Velocity>("Velocity");
    RegisterComponentArray<Destructible>("Destructible");
    RegisterComponentArray<Position>("Position");
    RegisterComponentArray<Rotation>("Rotation");
    RegisterComponentArray<Scale>("Scale");

    RegisterComponent<Spawner>("Spawner");
    RegisterComponent<Sprite>("Sprite");
    RegisterComponent<BoundaryBox>("BoundaryBox");
    RegisterComponent<CircleCollider>("CircleCollider");
    RegisterComponent<Player>("Player");

    ComponentAllocator::RegisterTag("Bullet");
    ComponentAllocator::RegisterTag("Bullet Pool");
    ComponentAllocator::RegisterTag("Spawner");
  }

  void ObjectManager::RegisterCustomSystems()
  {
    RegisterSystem<CreationSystem>("CreationSystem");
    RegisterSystem<DestructionSystem>("DestructionSystem");
    RegisterSystem<CollisionSystem>("CollisionSystem");
    RegisterSystem<MovementSystem>("MovementSystem");
    RegisterSystem<SpawnSystem>("SpawnSystem");
  }

  void ObjectManager::RegisterCustomSpawnFunctions()
  {
    RegisterSpawnFunction("MatchPosition", Spawn::MatchPosition);
    RegisterSpawnFunction("RandomDirection", Spawn::RandomDirection);
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