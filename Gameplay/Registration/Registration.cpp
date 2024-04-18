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
#include "Behavior/Action/Direction/Rotate/BehaviorRotateDirection.hpp"
#include "Behavior/Action/Wait/BehaviorWait.hpp"

#include "Behavior/Composite/Selector/BehaviorSelector.hpp"
#include "Behavior/Composite/Sequence/BehaviorSequence.hpp"

#include "Behavior/Decorator/AlwaysFail/BehaviorAlwaysFail.hpp"
#include "Behavior/Decorator/AlwaysSucceed/BehaviorAlwaysSucceed.hpp"
#include "Behavior/Decorator/Invert/BehaviorInvert.hpp"
#include "Behavior/Decorator/LoopOnSuccess/BehaviorLoopOnSuccess.hpp"
#include "Behavior/Decorator/LoopOnFailure/BehaviorLoopOnFailure.hpp"
#include "Behavior/Decorator/Repeat/BehaviorRepeat.hpp"

#include "Behavior/Parallel/Selector/BehaviorParallelSelector.hpp"
#include "Behavior/Parallel/Sequence/BehaviorParallelSequence.hpp"

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

#include "SpawnRules/Color/Set/SpawnSetColor.hpp"

#include "SpawnRules/Count/Iterate/SpawnIterateCount.hpp"

#include "SpawnRules/Direction/MatchSpawner/SpawnMatchSpawnerDirection.hpp"
#include "SpawnRules/Direction/Random/SpawnRandomDirection.hpp"
#include "SpawnRules/Direction/Set/SpawnSetDirection.hpp"

#include "SpawnRules/Miscellaneous/Fan/SpawnFan.hpp"
#include "SpawnRules/Miscellaneous/Mirror/SpawnMirror.hpp"
#include "SpawnRules/Miscellaneous/Ring/SpawnRing.hpp"

#include "SpawnRules/Orientation/Adjust/SpawnAdjustOrientation.hpp"
#include "SpawnRules/Orientation/Iterate/SpawnIterateOrientation.hpp"
#include "SpawnRules/Orientation/Random/SpawnRandomOrientation.hpp"

#include "SpawnRules/Position/Adjust/SpawnAdjustPosition.hpp"
#include "SpawnRules/Position/MatchSpawner/SpawnMatchSpawnerPosition.hpp"
#include "SpawnRules/Position/RandomBoxOffset/SpawnRandomBoxOffset.hpp"

#include "SpawnRules/Rotation/MatchDirection/SpawnRotationMatchDirection.hpp"

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
    RegisterBehaviorNode<Behavior::RotateDirection>("RotateDirection");
    RegisterBehaviorNode<Behavior::Wait>("Wait");
    
    RegisterBehaviorNode<Behavior::Selector>("Selector");
    RegisterBehaviorNode<Behavior::Sequence>("Sequence");

    RegisterBehaviorNode<Behavior::AlwaysFail>("AlwaysFail");
    RegisterBehaviorNode<Behavior::AlwaysSucceed>("AlwaysSucceed");
    RegisterBehaviorNode<Behavior::Invert>("Invert");
    RegisterBehaviorNode<Behavior::LoopOnFailure>("LoopOnFailure");
    RegisterBehaviorNode<Behavior::LoopOnSuccess>("LoopOnSuccess");
    RegisterBehaviorNode<Behavior::Repeat>("Repeat");
    
    RegisterBehaviorNode<Behavior::ParallelSelector>("ParallelSelector");
    RegisterBehaviorNode<Behavior::ParallelSequence>("ParallelSequence");

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
    
    RegisterSpawnRule<Spawn::SetColor>("SetColor");

    RegisterSpawnRule<Spawn::IterateCount>("IterateCount");

    RegisterSpawnRule<Spawn::MatchSpawnerDirection>("MatchSpawnerDirection");
    RegisterSpawnRule<Spawn::RandomDirection>("RandomDirection");
    RegisterSpawnRule<Spawn::SetDirection>("SetDirection");

    RegisterSpawnRule<Spawn::Fan>("Fan");
    RegisterSpawnRule<Spawn::Mirror>("Mirror");
    RegisterSpawnRule<Spawn::Ring>("Ring");

    RegisterSpawnRule<Spawn::AdjustOrientation>("AdjustOrientation");
    RegisterSpawnRule<Spawn::IterateOrientation>("IterateOrientation");
    RegisterSpawnRule<Spawn::RandomOrientation>("RandomOrientation");

    RegisterSpawnRule<Spawn::AdjustPosition>("AdjustPosition");
    RegisterSpawnRule<Spawn::MatchSpawnerPosition>("MatchSpawnerPosition");
    RegisterSpawnRule<Spawn::RandomBoxOffset>("RandomBoxOffset");

    RegisterSpawnRule<Spawn::RotationMatchDirection>("RotationMatchDirection");

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

    update_order.push_back("BehaviorSystem");
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
    Behavior::RotateDirection::Reflect();
    Behavior::Wait::Reflect();
    
    Behavior::Repeat::Reflect();

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

    Spawn::SetColor::Reflect();

    Spawn::IterateCount::Reflect();

    Spawn::SetDirection::Reflect();

    Spawn::Fan::Reflect();

    Spawn::AdjustOrientation::Reflect();
    Spawn::IterateOrientation::Reflect();

    Spawn::AdjustPosition::Reflect();
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