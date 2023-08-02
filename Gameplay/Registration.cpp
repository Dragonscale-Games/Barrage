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
#include "SpawnFunctions/Speed/SpeedRules.hpp"

namespace Barrage
{
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
    // Draw system is registered automatically by engine
    RegisterSystem<MovementSystem>("MovementSystem");
    RegisterSystem<SpawnSystem>("SpawnSystem");
  }

  void ObjectManager::RegisterCustomSpawnFunctions()
  {
    RegisterSpawnRule<Spawn::RandomDirection>("RandomDirection");
    RegisterSpawnRule<Spawn::RotateDirection>("RotateDirection");

    RegisterSpawnRule<Spawn::SpawnRing>("SpawnRing");

    RegisterSpawnRule<Spawn::MatchPosition>("MatchPosition");

    RegisterSpawnRule<Spawn::RandomSpeed>("RandomSpeed");
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