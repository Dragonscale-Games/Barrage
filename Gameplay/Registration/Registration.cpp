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

#include "ComponentArrays/AngularSpeed/AngularSpeedArray.hpp"
#include "ComponentArrays/ColorTint/ColorTintArray.hpp"
#include "ComponentArrays/Destructible/DestructibleArray.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"
#include "ComponentArrays/Rotation/RotationArray.hpp"
#include "ComponentArrays/Scale/ScaleArray.hpp"
#include "ComponentArrays/SpawnTimer/SpawnTimerArray.hpp"
#include "ComponentArrays/TextureUV/TextureUVArray.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"

#include "Components/BoundaryBox/BoundaryBox.hpp"
#include "Components/CircleCollider/CircleCollider.hpp"
#include "Components/Player/Player.hpp"
#include "Components/Spawner/Spawner.hpp"
#include "Components/Sprite/Sprite.hpp"

#include "SpawnRules/Direction/Random/SpawnRandomDirection.hpp"
#include "SpawnRules/Direction/Set/SpawnSetDirection.hpp"

#include "SpawnRules/Miscellaneous/Fan/SpawnFan.hpp"
#include "SpawnRules/Miscellaneous/Mirror/SpawnMirror.hpp"
#include "SpawnRules/Miscellaneous/Ring/SpawnRing.hpp"

#include "SpawnRules/Position/Match/SpawnMatchPosition.hpp"
#include "SpawnRules/Position/Offset/SpawnOffsetPosition.hpp"
#include "SpawnRules/Position/RandomBoxOffset/SpawnRandomBoxOffset.hpp"

#include "SpawnRules/Speed/Random/SpawnRandomSpeed.hpp"
#include "SpawnRules/Speed/Set/SpawnSetSpeed.hpp"

#include "Systems/Collision/CollisionSystem.hpp"
#include "Systems/Creation/CreationSystem.hpp"
#include "Systems/Destruction/DestructionSystem.hpp"
#include "Systems/Draw/DrawSystem.hpp"
#include "Systems/Movement/MovementSystem.hpp"
#include "Systems/Spawn/SpawnSystem.hpp"

namespace Barrage
{
  void Registrar::GameplayRegistration()
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

    RegisterComponent<BoundaryBox>("BoundaryBox");
    RegisterComponent<CircleCollider>("CircleCollider");
    RegisterComponent<Player>("Player");
    RegisterComponent<Sprite>("Sprite");
    RegisterComponent<Spawner>("Spawner");
    
    RegisterSpawnRule<Spawn::RandomDirection>("RandomDirection");
    RegisterSpawnRule<Spawn::SetDirection>("SetDirection");

    RegisterSpawnRule<Spawn::Fan>("Fan");
    RegisterSpawnRule<Spawn::Mirror>("Mirror");
    RegisterSpawnRule<Spawn::Ring>("Ring");

    RegisterSpawnRule<Spawn::MatchPosition>("MatchPosition");
    RegisterSpawnRule<Spawn::OffsetPosition>("OffsetPosition");
    RegisterSpawnRule<Spawn::RandomBoxOffset>("RandomBoxOffset");

    RegisterSpawnRule<Spawn::RandomSpeed>("RandomSpeed");
    RegisterSpawnRule<Spawn::SetSpeed>("SetSpeed");

    RegisterSystem<CollisionSystem>("CollisionSystem");
    RegisterSystem<CreationSystem>("CreationSystem");
    RegisterSystem<DestructionSystem>("DestructionSystem");
    RegisterSystem<DrawSystem>("DrawSystem");
    RegisterSystem<MovementSystem>("MovementSystem");
    RegisterSystem<SpawnSystem>("SpawnSystem");
    
    RegisterTag("Bullet");

    std::vector<std::string> update_order;

    update_order.push_back("CreationSystem");
    update_order.push_back("DestructionSystem");
    update_order.push_back("MovementSystem");
    update_order.push_back("SpawnSystem");
    update_order.push_back("CreationSystem");
    update_order.push_back("CollisionSystem");

    SetSystemUpdateOrder(update_order);
  }

  void Registrar::GameplayReflection()
  {
    AngularSpeed::Reflect();
    ColorTintReflect();
    DestructibleReflect();
    PositionReflect();
    RotationReflect();
    ScaleReflect();
    SpawnTimer::Reflect();
    TextureUVReflect();
    Velocity::Reflect();

    BoundaryBox::Reflect();
    CircleCollider::Reflect();
    Player::Reflect();
    Spawner::Reflect();
    Sprite::Reflect();

    Spawn::SetDirection::Reflect();

    Spawn::Fan::Reflect();

    Spawn::OffsetPosition::Reflect();
    Spawn::RandomBoxOffset::Reflect();

    Spawn::RandomSpeed::Reflect();
    Spawn::SetSpeed::Reflect();
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