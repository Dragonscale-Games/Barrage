/* ======================================================================== */
/*!
 * \file            ObjectManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The main point of contact for game object manipulation in the engine.
 */
/* ======================================================================== */

#include "stdafx.h"
#include "ObjectManager.hpp"

#include "Components/EngineComponents.hpp"
#include "Systems/EngineSystems.hpp"
#include "Spaces/Space.hpp"

namespace Barrage
{
  ObjectManager::ObjectManager(Space& space) :
    rng_(),
    componentAllocator_(),
    poolManager_(componentAllocator_, space),
    systemManager_(),
    spawnFunctionManager_()
  {
    RegisterEngineComponents();
    RegisterEngineSystems();
    RegisterEngineSpawnFunctions();
    SetDefaultSystemUpdateOrder();

    CreationSystem* creation_system = dynamic_cast<CreationSystem*>(systemManager_.systems_.at("CreationSystem"));

    creation_system->SetSpawnFunctionManager(spawnFunctionManager_);
    creation_system->SetPoolManager(poolManager_);

    RegisterCustomComponents();
    RegisterCustomSystems();
    RegisterCustomSpawnFunctions();
    SetSystemUpdateOrder();
  }

  void ObjectManager::Update()
  {
    systemManager_.Update();
  }

  void ObjectManager::Draw()
  {
    DrawSystem* draw_system = dynamic_cast<DrawSystem*>(systemManager_.systems_["DrawSystem"]);

    if (draw_system)
    {
      draw_system->Draw();
    }
  }

  /*void ObjectManager::CreateObject(const std::string& poolName, const std::string& archetypeName)
  {
    Pool* pool = poolManager_.GetPool(poolName);
    ObjectArchetype* archetype = archetypeManager_.GetObjectArchetype(archetypeName);

    CreationSystem* creation_system = dynamic_cast<CreationSystem*>(systemManager_.systems_["CreationSystem"]);

    if (pool && archetype && creation_system)
    {
      creation_system->CreateObject(*archetype, pool);
    }
  }*/

  std::vector<std::string_view> ObjectManager::GetComponentArrayNames()
  {
    return componentAllocator_.GetComponentArrayNames();
  }

  std::vector<std::string_view> ObjectManager::GetSharedComponentNames()
  {
    return componentAllocator_.GetSharedComponentNames();
  }

  ComponentAllocator& ObjectManager::GetComponentAllocator()
  {
    return componentAllocator_;
  }

  std::vector<std::string_view> ObjectManager::GetSpawnFunctionNames()
  {
    return spawnFunctionManager_.GetSpawnFunctionNames();
  }

  std::vector<std::string_view> ObjectManager::GetRegisteredSystemNames()
  {
    return systemManager_.GetRegisteredSystemNames();
  }

  std::vector<std::string_view> ObjectManager::GetSystemUpdateOrder()
  {
    return systemManager_.GetSystemUpdateOrder();
  }

  void ObjectManager::CreatePool(const PoolArchetype& archetype)
  {
    if (archetype.capacity_ == 0)
      return;
    
    CreationSystem* creation_system = dynamic_cast<CreationSystem*>(systemManager_.systems_["CreationSystem"]);
    Pool* new_pool = poolManager_.CreatePool(archetype);

    for (auto it = archetype.startingObjects_.begin(); it != archetype.startingObjects_.end(); ++it)
    {
      if (creation_system)
      {
        creation_system->CreateObject(*it, new_pool);
      }
    }

    systemManager_.Subscribe(new_pool);
  }

  Pool* ObjectManager::GetPool(const std::string& name) const
  {
    return poolManager_.GetPool(name);
  }

  void ObjectManager::DeletePool(const std::string& poolName)
  {
    Pool* pool = poolManager_.GetPool(poolName);

    if (pool)
    {
      systemManager_.Unsubscribe(pool);
      poolManager_.DeletePool(poolName);
    }
  }

  void ObjectManager::DeleteAllPools()
  {
    std::vector<std::string> pool_names = GetPoolNames();

    for (auto it = pool_names.begin(); it != pool_names.end(); ++it)
    {
      DeletePool(*it);
    }
  }

  std::vector<std::string> ObjectManager::GetPoolNames()
  {
    return poolManager_.GetPoolNames();
  }

  void ObjectManager::SetSystemUpdateOrder(const std::vector<std::string_view>& updateOrderList)
  {
    systemManager_.SetUpdateOrder(updateOrderList);
  }

  void ObjectManager::RegisterSpawnFunction(const std::string_view& name, SpawnFunction initializer)
  {
    spawnFunctionManager_.RegisterSpawnFunction(name, initializer);
  }

  void ObjectManager::RegisterEngineComponents()
  {
    RegisterComponentArray<Destructible>("Destructible");
    RegisterComponentArray<DirectoryIndex>("DirectoryIndex");
    RegisterComponentArray<Parent>("Parent");
    RegisterComponentArray<Position>("Position");
    RegisterComponentArray<Rotation>("Rotation");
    RegisterComponentArray<Scale>("Scale");
    RegisterComponentArray<TextureSpace>("TextureSpace");

    RegisterSharedComponent<ObjectDirectory>("ObjectDirectory");
    RegisterSharedComponent<Spawner>("Spawner");
    RegisterSharedComponent<Sprite>("Sprite");
  }

  void ObjectManager::RegisterEngineSystems()
  {
    RegisterSystem<CreationSystem>("CreationSystem");
    RegisterSystem<DestructionSystem>("DestructionSystem");
    RegisterSystem<DrawSystem>("DrawSystem");
  }

  void ObjectManager::RegisterEngineSpawnFunctions()
  {

  }

  void ObjectManager::SetDefaultSystemUpdateOrder()
  {
    std::vector<std::string_view> update_order;

    update_order.push_back("CreationSystem");
    update_order.push_back("DestructionSystem");

    SetSystemUpdateOrder(update_order);
  }
}