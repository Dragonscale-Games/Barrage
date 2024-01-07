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

#include "Registration/Registrar.hpp"
#include "Objects/ObjectManager.hpp"

#include "ComponentArrays/AngularSpeedArray.hpp"
#include "ComponentArrays/ColorTintArray.hpp"
#include "ComponentArrays/DestructibleArray.hpp"
#include "ComponentArrays/PositionArray.hpp"
#include "ComponentArrays/RotationArray.hpp"
#include "ComponentArrays/ScaleArray.hpp"
#include "ComponentArrays/SpawnTimerArray.hpp"
#include "ComponentArrays/TextureUVArray.hpp"
#include "ComponentArrays/VelocityArray.hpp"

#include "Components/BoundaryBox.hpp"
#include "Components/CircleCollider.hpp"
#include "Components/Player.hpp"
#include "Components/Spawner.hpp"
#include "Components/Sprite.hpp"

#include "SpawnRules/Position/PositionRules.hpp"

#include "Systems/Collision/CollisionSystem.hpp"
#include "Systems/Creation/CreationSystem.hpp"
#include "Systems/Destruction/DestructionSystem.hpp"
#include "Systems/Draw/DrawSystem.hpp"
#include "Systems/Movement/MovementSystem.hpp"
#include "Systems/Spawn/SpawnSystem.hpp"

namespace Barrage
{
  void Registrar::Registration()
  {
    RegisterComponentArray<AngularSpeed>("AngularSpeed");
    RegisterComponentArray<ColorTint>("ColorTint");
    RegisterComponentArray<Destructible>("Destructible");
    RegisterComponentArray<Position>("Position");
    RegisterComponentArray<Rotation>("Rotation");
    RegisterComponentArray<Scale>("Scale");
    RegisterComponentArray<SpawnTimer>("SpawnTimer");
    RegisterComponentArray<TextureUV>("TextureUV");
    RegisterComponentArray<Velocity>("Velocity");

    RegisterComponent<Sprite>("Sprite");
    RegisterComponent<Spawner>("Spawner");
    
    RegisterSpawnRule<Spawn::MatchPosition>("MatchPosition");
    RegisterSpawnRule<Spawn::RandomOffset>("RandomOffset");

    RegisterSystem<CollisionSystem>("CollisionSystem");
    RegisterSystem<CreationSystem>("CreationSystem");
    RegisterSystem<DestructionSystem>("DestructionSystem");
    RegisterSystem<DrawSystem>("DrawSystem");
    RegisterSystem<MovementSystem>("MovementSystem");
    RegisterSystem<SpawnSystem>("SpawnSystem");
    

    std::vector<std::string> update_order;

    update_order.push_back("CreationSystem");
    update_order.push_back("DestructionSystem");
    update_order.push_back("MovementSystem");
    update_order.push_back("SpawnSystem");
    update_order.push_back("CreationSystem");
    update_order.push_back("CollisionSystem");

    SetSystemUpdateOrder(update_order);
  }

  void ObjectManager::Draw()
  {
    std::shared_ptr<DrawSystem> drawSystem = std::dynamic_pointer_cast<DrawSystem>(systemManager_.GetSystem("DrawSystem"));
    
    if (drawSystem)
    {
      drawSystem->Draw();
    }
  }
}