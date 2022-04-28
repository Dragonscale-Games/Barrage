/* ======================================================================== */
/*!
 * \file            GameRegistration.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Functions for registering all custom game systems, components, and
   initializers.
 */
 /* ======================================================================== */

#include "Objects/ObjectManager.hpp"

#include "Objects/Components/GameComponents.hpp"
#include "Objects/Systems/GameSystems.hpp"
#include "Objects/Initializers/GameInitializers.hpp"

namespace Barrage
{
  void ObjectManager::RegisterCustomComponents()
  {
    RegisterComponent<CircleCollider>("CircleCollider");
    RegisterComponent<Velocity>("Velocity");

    RegisterComponent<RNG>("RNG");
    RegisterComponent<Timer>("Timer");
  }

  void ObjectManager::RegisterCustomSystems()
  {
    RegisterSystem<CollisionSystem>("Collision System");
    RegisterSystem<MovementSystem>("Movement System");
    RegisterSystem<TimerSystem>("Timer System");
    RegisterSystem<WaveformSystem>("Waveform System");
  }

  void ObjectManager::RegisterCustomInitializers()
  {
    RegisterInitializer("Random Direction", Initializers::RandomDirection);
    RegisterInitializer("Circle Spawn", Initializers::CircleSpawn);
  }

  void ObjectManager::SetCustomSystemUpdateOrder()
  {
    SystemList update_order;

    update_order.push_back("Timer System");
    update_order.push_back("Waveform System");
    update_order.push_back("Movement System");
    update_order.push_back("Creation System");
    update_order.push_back("Collision System");
    update_order.push_back("Destruction System");
    update_order.push_back("Draw System");

    SetSystemUpdateOrder(update_order);
  }
}