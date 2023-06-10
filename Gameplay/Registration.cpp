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

#include "ComponentArrays/AngularSpeedArray.hpp"
#include "ComponentArrays/VelocityArray.hpp"

#include "Components/BoundaryBox.hpp"
#include "Components/CircleCollider.hpp"
#include "Components/Player.hpp"
#include "Components/RNG.hpp"

#include "Systems/Collision/CollisionSystem.hpp"
#include "Systems/Movement/MovementSystem.hpp"
#include "Systems/Spawn/SpawnSystem.hpp"

#include "SpawnFunctions/Direction/DirectionFuncs.hpp"
#include "SpawnFunctions/Position/PositionFuncs.hpp"

namespace Barrage
{
  void ReflectBarrageCore()
  {
    rttr::registration::class_<BoundaryBox>("BoundaryBox")
      .property("xMin", &BoundaryBox::xMin_)
      .property("xMax", &BoundaryBox::xMax_)
      .property("yMin", &BoundaryBox::yMin_)
      .property("yMax", &BoundaryBox::yMax_)
      ;

    rttr::registration::class_<CircleCollider>("CircleCollider")
      .property("radius", &CircleCollider::radius_)
      ;

    rttr::registration::class_<Player>("Player")
      .property("speedFast", &Player::speedFast_)
      .property("speedSlow", &Player::speedSlow_)
      ;

    rttr::registration::class_<Sprite>("Sprite")
      .property("texture", &Sprite::texture_)
      .property("layer", &Sprite::layer_)
      ;

    rttr::registration::class_<Spawner>("Spawner")
      .property("spawnTypes", &Spawner::spawnTypes_)
      ;

    rttr::registration::class_<SpawnInfo>("SpawnInfo")
      .property("archetypeName", &SpawnInfo::archetypeName_)
      .property("spawnFunctions", &SpawnInfo::spawnFunctions_)
      .constructor<>()
        (
          rttr::policy::ctor::as_object
        );
      ;

    rttr::registration::class_<Position>("Position")
      .property("x", &Position::x_)
      .property("y", &Position::y_)
      ;

    rttr::registration::class_<Rotation>("Rotation")
      .property("angle", &Rotation::angle_)
      ;

    rttr::registration::class_<Scale>("Scale")
      .property("w", &Scale::w_)
      .property("h", &Scale::h_)
      ;

    rttr::registration::class_<TextureSpace>("TextureSpace")
      .property("u", &TextureSpace::u_)
      .property("v", &TextureSpace::v_)
      .property("uSize", &TextureSpace::uSize_)
      .property("vSize", &TextureSpace::vSize_)
      ;

    rttr::registration::class_<AngularSpeed>("AngularSpeed")
      .property("w", &AngularSpeed::w_)
      ;
  }
  
  void ObjectManager::RegisterCustomComponents()
  {
    RegisterComponentArray<AngularSpeed>("AngularSpeed");
    RegisterComponentArray<Velocity>("Velocity");

    RegisterComponent<BoundaryBox>("BoundaryBox");
    RegisterComponent<CircleCollider>("CircleCollider");
    RegisterComponent<Player>("Player");
    RegisterComponent<RNG>("RNG");

    ComponentAllocator::RegisterTag("Bullet");
    ComponentAllocator::RegisterTag("Bullet Pool");
    ComponentAllocator::RegisterTag("Spawner");
  }

  void ObjectManager::RegisterCustomSystems()
  {
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