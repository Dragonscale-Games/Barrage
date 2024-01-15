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
#include "SpawnRules/Direction/Rotate/SpawnRotateDirection.hpp"
#include "SpawnRules/Direction/Set/SpawnSetDirection.hpp"

#include "SpawnRules/Miscellaneous/Mirror/SpawnMirror.hpp"
#include "SpawnRules/Miscellaneous/Ring/SpawnRing.hpp"
#include "SpawnRules/Miscellaneous/SpacedFan/SpawnSpacedFan.hpp"
#include "SpawnRules/Miscellaneous/SpanFan/SpawnSpanFan.hpp"

#include "SpawnRules/Position/Match/SpawnMatchPosition.hpp"
#include "SpawnRules/Position/OffsetGlobal/SpawnOffsetGlobal.hpp"
#include "SpawnRules/Position/OffsetLocal/SpawnOffsetLocal.hpp"
#include "SpawnRules/Position/RandomBoxOffset/SpawnRandomBoxOffset.hpp"
#include "SpawnRules/Position/RandomCircleOffset/SpawnRandomCircleOffset.hpp"
#include "SpawnRules/Position/RotateOrigin/SpawnRotateOrigin.hpp"
#include "SpawnRules/Position/ScaleOrigin/SpawnScaleOrigin.hpp"

#include "SpawnRules/Speed/Increment/SpawnIncrementSpeed.hpp"
#include "SpawnRules/Speed/Random/SpawnRandomSpeed.hpp"

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
    RegisterSpawnRule<Spawn::RotateDirection>("RotateDirection");
    RegisterSpawnRule<Spawn::SetDirection>("SetDirection");

    RegisterSpawnRule<Spawn::Mirror>("Mirror");
    RegisterSpawnRule<Spawn::Ring>("Ring");
    RegisterSpawnRule<Spawn::SpacedFan>("SpacedFan");
    RegisterSpawnRule<Spawn::SpanFan>("SpanFan");

    RegisterSpawnRule<Spawn::MatchPosition>("MatchPosition");
    RegisterSpawnRule<Spawn::OffsetGlobal>("OffsetGlobal");
    RegisterSpawnRule<Spawn::OffsetLocal>("OffsetLocal");
    RegisterSpawnRule<Spawn::RandomBoxOffset>("RandomBoxOffset");
    RegisterSpawnRule<Spawn::RandomCircleOffset>("RandomCircleOffset");
    RegisterSpawnRule<Spawn::RotateOrigin>("RotateOrigin");
    RegisterSpawnRule<Spawn::ScaleOrigin>("ScaleOrigin");

    RegisterSpawnRule<Spawn::IncrementSpeed>("IncrementSpeed");
    RegisterSpawnRule<Spawn::RandomSpeed>("RandomSpeed");

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

    Spawn::RotateDirection::Reflect();
    Spawn::SetDirection::Reflect();

    Spawn::OffsetGlobal::Reflect();
    Spawn::RandomBoxOffset::Reflect();

    Spawn::IncrementSpeed::Reflect();
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