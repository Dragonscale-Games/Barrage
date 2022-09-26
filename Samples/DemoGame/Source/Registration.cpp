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

namespace Barrage
{
  void ObjectManager::RegisterCustomComponents()
  {
    RegisterComponent<Demo::AngularSpeedArray>("AngularSpeedArray");
    RegisterComponent<Demo::VelocityArray>("VelocityArray");

    RegisterComponent<Demo::BoundaryBox>("BoundaryBox");
    RegisterComponent<Demo::CircleCollider>("CircleCollider");
    RegisterComponent<Demo::Player>("Player");
    RegisterComponent<Demo::RNG>("RNG");
  }

  void ObjectManager::RegisterCustomSystems()
  {
    RegisterSystem<Demo::CollisionSystem>("CollisionSystem");
    RegisterSystem<Demo::MovementSystem>("MovementSystem");
    RegisterSystem<Demo::SpawnSystem>("SpawnSystem");
  }

  void ObjectManager::RegisterCustomSpawnFuncs()
  {
    RegisterSpawnFunc("MatchPosition", Demo::Spawn::MatchPosition);
    RegisterSpawnFunc("RandomDirection", Demo::Spawn::RandomDirection);
  }

  void ObjectManager::SetSystemUpdateOrder()
  {
    std::vector<std::string> update_order;

    update_order.push_back("CreationSystem");
    update_order.push_back("DestructionSystem");
    update_order.push_back("MovementSystem");
    update_order.push_back("SpawnSystem");
    update_order.push_back("CreationSystem");
    update_order.push_back("CollisionSystem");

    SetSystemUpdateOrder(update_order);
  }
}