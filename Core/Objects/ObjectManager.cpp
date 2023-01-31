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
    archetypeManager_(componentAllocator_),
    poolManager_(componentAllocator_, space),
    systemManager_(),
    spawnFuncManager_()
  {
    RegisterEngineComponents();
    RegisterEngineSystems();
    RegisterEngineSpawnFuncs();
    SetDefaultSystemUpdateOrder();

    CreationSystem* creation_system = dynamic_cast<CreationSystem*>(systemManager_.systems_.at("CreationSystem"));

    creation_system->SetArchetypeManager(archetypeManager_);
    creation_system->SetSpawnFuncManager(spawnFuncManager_);
    creation_system->SetPoolManager(poolManager_);

    RegisterCustomComponents();
    RegisterCustomSystems();
    RegisterCustomSpawnFuncs();
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

  void ObjectManager::CreateObject(const std::string& poolName, const std::string& archetypeName)
  {
    Pool* pool = poolManager_.GetPool(poolName);
    ObjectArchetype* archetype = archetypeManager_.GetObjectArchetype(archetypeName);

    CreationSystem* creation_system = dynamic_cast<CreationSystem*>(systemManager_.systems_["CreationSystem"]);

    if (pool && archetype && creation_system)
    {
      creation_system->CreateObject(*archetype, pool);
    }
  }

  std::vector<std::string> ObjectManager::GetComponentArrayNames()
  {
    return componentAllocator_.GetComponentArrayNames();
  }

  std::vector<std::string> ObjectManager::GetSharedComponentNames()
  {
    return componentAllocator_.GetSharedComponentNames();
  }

  std::vector<std::string> ObjectManager::GetSpawnFuncNames()
  {
    return spawnFuncManager_.GetSpawnFuncNames();
  }

  std::vector<std::string> ObjectManager::GetRegisteredSystemNames()
  {
    return systemManager_.GetRegisteredSystemNames();
  }

  std::vector<std::string> ObjectManager::GetSystemUpdateOrder()
  {
    return systemManager_.GetSystemUpdateOrder();
  }

  void ObjectManager::AddPoolArchetype(const std::string& name, PoolArchetype* archetype)
  {
    archetypeManager_.AddPoolArchetype(name, archetype);
  }

  void ObjectManager::AddObjectArchetype(const std::string& name, ObjectArchetype* archetype)
  {
    archetypeManager_.AddObjectArchetype(name, archetype);
  }

  std::vector<std::string> ObjectManager::GetPoolArchetypeNames()
  {
    return archetypeManager_.GetPoolArchetypeNames();
  }

  std::vector<std::string> ObjectManager::GetObjectArchetypeNames()
  {
    return archetypeManager_.GetObjectArchetypeNames();
  }

  void ObjectManager::CreatePool(const std::string& poolName, const std::string& archetypeName, unsigned capacity)
  {
    if (capacity == 0)
      return;

    PoolArchetype* pool_archetype = archetypeManager_.GetPoolArchetype(archetypeName);
    
    if (pool_archetype)
    {
      Pool* new_pool = poolManager_.CreatePool(poolName, *pool_archetype, capacity);
      systemManager_.Subscribe(new_pool);
    }
  }

  void ObjectManager::CreatePoolAndObjects(const PoolInfo& poolInfo)
  {
    CreatePool(poolInfo.poolName_, poolInfo.archetypeName_, poolInfo.capacity_);

    for (auto it = poolInfo.objects_.begin(); it != poolInfo.objects_.end(); ++it)
    {
      CreateObject(poolInfo.poolName_, *it);
    }
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

  void ObjectManager::SetSystemUpdateOrder(const std::vector<std::string>& updateOrderList)
  {
    systemManager_.SetUpdateOrder(updateOrderList);
  }

  void ObjectManager::RegisterSpawnFunc(const std::string& name, SpawnFunc initializer)
  {
    spawnFuncManager_.RegisterSpawnFunc(name, initializer);
  }

  void ObjectManager::RegisterEngineComponents()
  {
    RegisterComponent<DestructibleArray>("DestructibleArray");
    RegisterComponent<DirectoryIndexArray>("DirectoryIndexArray");
    RegisterComponent<ParentArray>("ParentArray");
    RegisterComponent<PositionArray>("PositionArray");
    RegisterComponent<RotationArray>("RotationArray");
    RegisterComponent<ScaleArray>("ScaleArray");
    RegisterComponent<TextureSpaceArray>("TextureSpaceArray");

    RegisterComponent<ObjectDirectory>("ObjectDirectory");
    RegisterComponent<Spawner>("Spawner");
    RegisterComponent<Sprite>("Sprite");
  }

  void ObjectManager::RegisterEngineSystems()
  {
    RegisterSystem<CreationSystem>("CreationSystem");
    RegisterSystem<DestructionSystem>("DestructionSystem");
    RegisterSystem<DrawSystem>("DrawSystem");
  }

  void ObjectManager::RegisterEngineSpawnFuncs()
  {

  }

  void ObjectManager::SetDefaultSystemUpdateOrder()
  {
    std::vector<std::string> update_order;

    update_order.push_back("CreationSystem");
    update_order.push_back("DestructionSystem");

    SetSystemUpdateOrder(update_order);
  }
}