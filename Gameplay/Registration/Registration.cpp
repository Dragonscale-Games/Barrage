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

#include "Behavior/Action/Debug/BehaviorDebug.hpp"

#include "Behavior/Composite/Selector/BehaviorSelector.hpp"
#include "Behavior/Composite/Sequence/BehaviorSequence.hpp"

#include "Behavior/Decorator/Loop/BehaviorLoop.hpp"
#include "Behavior/Decorator/Repeat/BehaviorRepeat.hpp"
#include "Behavior/Decorator/Wait/BehaviorWait.hpp"

#include "ComponentArrays/AngularSpeed/AngularSpeedArray.hpp"
#include "ComponentArrays/ColorTint/ColorTintArray.hpp"
#include "ComponentArrays/Destructible/DestructibleArray.hpp"
#include "ComponentArrays/Lifetime/LifetimeArray.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"
#include "ComponentArrays/Rotation/RotationArray.hpp"
#include "ComponentArrays/Scale/ScaleArray.hpp"
#include "ComponentArrays/TextureUV/TextureUVArray.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"

#include "Components/Behavior/Behavior.hpp"
#include "Components/BoundaryBox/BoundaryBox.hpp"
#include "Components/CircleCollider/CircleCollider.hpp"
#include "Components/Movement/Movement.hpp"
#include "Components/Player/Player.hpp"
#include "Components/Spawner/Spawner.hpp"
#include "Components/Sprite/Sprite.hpp"

#include "SpawnRules/Count/Increment/SpawnIncrementCount.hpp"

#include "SpawnRules/Direction/Aimed/SpawnAimedDirection.hpp"
#include "SpawnRules/Direction/Match/SpawnMatchDirection.hpp"
#include "SpawnRules/Direction/Random/SpawnRandomDirection.hpp"
#include "SpawnRules/Direction/Set/SpawnSetDirection.hpp"

#include "SpawnRules/Miscellaneous/Fan/SpawnFan.hpp"
#include "SpawnRules/Miscellaneous/Mirror/SpawnMirror.hpp"
#include "SpawnRules/Miscellaneous/Ring/SpawnRing.hpp"
#include "SpawnRules/Miscellaneous/Spiral/SpawnSpiral.hpp"

#include "SpawnRules/Position/Match/SpawnMatchPosition.hpp"
#include "SpawnRules/Position/Offset/SpawnOffsetPosition.hpp"
#include "SpawnRules/Position/RandomBoxOffset/SpawnRandomBoxOffset.hpp"

#include "SpawnRules/Speed/Random/SpawnRandomSpeed.hpp"
#include "SpawnRules/Speed/Set/SpawnSetSpeed.hpp"

#include "Systems/Behavior/BehaviorSystem.hpp"
#include "Systems/Collision/CollisionSystem.hpp"
#include "Systems/Destruction/DestructionSystem.hpp"
#include "Systems/Draw/DrawSystem.hpp"
#include "Systems/Lifetime/LifetimeSystem.hpp"
#include "Systems/Movement/MovementSystem.hpp"
#include "Systems/Spawn/SpawnSystem.hpp"

namespace Barrage
{
  void Registrar::GameplayRegistration()
  {
    RegisterBehaviorNode<Behavior::Debug>("Debug");
    
    RegisterBehaviorNode<Behavior::Selector>("Selector");
    RegisterBehaviorNode<Behavior::Sequence>("Sequence");

    RegisterBehaviorNode<Behavior::Loop>("Loop");
    RegisterBehaviorNode<Behavior::Repeat>("Repeat");
    RegisterBehaviorNode<Behavior::Wait>("Wait");
    
    RegisterComponentArray<AngularSpeed>("AngularSpeed");
    RegisterComponentArray<ColorTint>("ColorTint");
    RegisterComponentArray<Destructible>("Destructible");
    RegisterComponentArray<Lifetime>("Lifetime");
    RegisterComponentArray<Position>("Position");
    RegisterComponentArray<Rotation>("Rotation");
    RegisterComponentArray<Scale>("Scale");
    RegisterComponentArray<TextureUV>("TextureUV");
    RegisterComponentArray<Velocity>("Velocity");

    RegisterComponent<BehaviorTree>("BehaviorTree");
    RegisterComponent<BoundaryBox>("BoundaryBox");
    RegisterComponent<CircleCollider>("CircleCollider");
    RegisterComponent<Movement>("Movement");
    RegisterComponent<Player>("Player");
    RegisterComponent<Sprite>("Sprite");
    RegisterComponent<Spawner>("Spawner");
    
    RegisterSpawnRule<Spawn::IncrementCount>("IncrementCount");

    RegisterSpawnRule<Spawn::AimedDirection>("AimedDirection");
    RegisterSpawnRule<Spawn::MatchDirection>("MatchDirection");
    RegisterSpawnRule<Spawn::RandomDirection>("RandomDirection");
    RegisterSpawnRule<Spawn::SetDirection>("SetDirection");

    RegisterSpawnRule<Spawn::Fan>("Fan");
    RegisterSpawnRule<Spawn::Mirror>("Mirror");
    RegisterSpawnRule<Spawn::Ring>("Ring");
    RegisterSpawnRule<Spawn::Spiral>("Spiral");

    RegisterSpawnRule<Spawn::MatchPosition>("MatchPosition");
    RegisterSpawnRule<Spawn::OffsetPosition>("OffsetPosition");
    RegisterSpawnRule<Spawn::RandomBoxOffset>("RandomBoxOffset");

    RegisterSpawnRule<Spawn::RandomSpeed>("RandomSpeed");
    RegisterSpawnRule<Spawn::SetSpeed>("SetSpeed");

    RegisterSystem<BehaviorSystem>("BehaviorSystem");
    RegisterSystem<CollisionSystem>("CollisionSystem");
    RegisterSystem<DestructionSystem>("DestructionSystem");
    RegisterSystem<DrawSystem>("DrawSystem");
    RegisterSystem<LifetimeSystem>("LifetimeSystem");
    RegisterSystem<MovementSystem>("MovementSystem");
    RegisterSystem<SpawnSystem>("SpawnSystem");
    
    RegisterTag("Bullet");

    std::vector<std::string> update_order;

    update_order.push_back("MovementSystem");
    update_order.push_back("DestructionSystem");
    update_order.push_back("LifetimeSystem");
    update_order.push_back("SpawnSystem");
    update_order.push_back("CollisionSystem");

    SetSystemUpdateOrder(update_order);
  }

  void Registrar::GameplayReflection()
  {
    Behavior::Debug::Reflect();
    
    Behavior::Wait::Reflect();
    
    AngularSpeed::Reflect();
    ColorTintReflect();
    DestructibleReflect();
    Lifetime::Reflect();
    PositionReflect();
    RotationReflect();
    ScaleReflect();
    TextureUVReflect();
    Velocity::Reflect();

    BoundaryBox::Reflect();
    CircleCollider::Reflect();
    Movement::Reflect();
    Player::Reflect();
    Spawner::Reflect();
    Sprite::Reflect();

    Spawn::IncrementCount::Reflect();

    Spawn::SetDirection::Reflect();

    Spawn::Fan::Reflect();
    Spawn::Spiral::Reflect();

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