/* ======================================================================== */
/*!
 * \file            GameRegistration.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   All games must define the functions below. These functions register all
   custom code for a game.

   Any number of these functions may be empty. If any function is empty, only
   the engine's defaults will be used.
 */
/* ======================================================================== */

#include <Objects/ObjectManager.hpp>

#include "Systems/DemoSystems.hpp"
#include "Components/DemoComponents.hpp"
#include "SpawnFuncs/DemoSpawnFuncs.hpp"
#include "Objects/Components/ComponentAllocator.hpp"

namespace Barrage
{
  void ObjectManager::RegisterCustomComponents()
  {
    RegisterComponentArray<Demo::AngularSpeed>("AngularSpeed");
    RegisterComponentArray<Demo::Velocity>("Velocity");

    RegisterComponent<Demo::BoundaryBox>("BoundaryBox");
    RegisterComponent<Demo::CircleCollider>("CircleCollider");
    RegisterComponent<Demo::Player>("Player");
    RegisterComponent<Demo::RNG>("RNG");

    ComponentAllocator::RegisterTag("Bullet");
    ComponentAllocator::RegisterTag("Bullet Pool");
    ComponentAllocator::RegisterTag("Spawner");
  }

  void ObjectManager::RegisterCustomSystems()
  {
    RegisterSystem<Demo::CollisionSystem>("CollisionSystem");
    RegisterSystem<Demo::MovementSystem>("MovementSystem");
    RegisterSystem<Demo::SpawnSystem>("SpawnSystem");
  }

  void ObjectManager::RegisterCustomSpawnFunctions()
  {
    RegisterSpawnFunction("MatchPosition", Demo::Spawn::MatchPosition);
    RegisterSpawnFunction("RandomDirection", Demo::Spawn::RandomDirection);
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