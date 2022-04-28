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
#include "Initializers/EngineInitializers.hpp"

namespace Barrage
{
  ObjectManager::ObjectManager() :
    componentAllocator_(),
    archetypeManager_(componentAllocator_),
    poolManager_(componentAllocator_),
    systemManager_(),
    initializerManager_()
  {
    RegisterComponent<Destructible>("Destructible");
    RegisterComponent<Position>("Position");
    RegisterComponent<Rotation>("Rotation");
    RegisterComponent<Scale>("Scale");

    RegisterComponent<Spawner>("Spawner");
    RegisterComponent<Sprite>("Sprite");
    RegisterComponent<Tags>("Tags");

    RegisterSystem<CreationSystem>("Creation System");
    RegisterSystem<DestructionSystem>("Destruction System");
    RegisterSystem<DrawSystem>("Draw System");

    CreationSystem* creation_system = dynamic_cast<CreationSystem*>(systemManager_.systems_.at("Creation System"));

    creation_system->SetArchetypeManager(archetypeManager_);
    creation_system->SetInitializerManager(initializerManager_);
    creation_system->SetPoolManager(poolManager_);

    RegisterCustomComponents();
    RegisterCustomSystems();
    RegisterCustomInitializers();
    SetCustomSystemUpdateOrder();
  }
  
  void ObjectManager::Update()
  {
    systemManager_.Update();
  }

  void ObjectManager::CreateObject(const std::string& poolName, const std::string& archetypeName)
  {
    Pool* pool = poolManager_.GetPool(poolName);
    ObjectArchetype* archetype = archetypeManager_.GetObjectArchetype(archetypeName);

    CreationSystem* creation_system = dynamic_cast<CreationSystem*>(systemManager_.systems_["Creation System"]);

    if (pool && archetype && creation_system)
    {
      creation_system->CreateObject(*archetype, pool);
    }
  }

  ObjectComponentList ObjectManager::GetObjectComponentNames()
  {
    return componentAllocator_.GetObjectComponentNames();
  }

  PoolComponentList ObjectManager::GetPoolComponentNames()
  {
    return componentAllocator_.GetPoolComponentNames();
  }

  InitializerList ObjectManager::GetInitializerNames()
  {
    return initializerManager_.GetInitializerNames();
  }

  SystemList ObjectManager::GetRegisteredSystemNames()
  {
    return systemManager_.GetRegisteredSystemNames();
  }

  SystemList ObjectManager::GetSystemUpdateOrder()
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

  ArchetypeList ObjectManager::GetPoolArchetypeNames()
  {
    return archetypeManager_.GetPoolArchetypeNames();
  }

  ArchetypeList ObjectManager::GetObjectArchetypeNames()
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
    const PoolList& pool_names = GetPoolNames();

    for (auto it = pool_names.begin(); it != pool_names.end(); ++it)
    {
      DeletePool(*it);
    }
  }

  const PoolList& ObjectManager::GetPoolNames()
  {
    return poolManager_.GetPoolNames();
  }

  void ObjectManager::SetSystemUpdateOrder(const SystemList& updateOrderList)
  {
    systemManager_.SetUpdateOrder(updateOrderList);
  }

  void ObjectManager::RegisterInitializer(const std::string name, Initializer initializer)
  {
    initializerManager_.RegisterInitializer(name, initializer);
  }

  void ObjectManager::Draw()
  {
    DrawSystem* draw_system = dynamic_cast<DrawSystem*>(systemManager_.systems_["Draw System"]);

    if (draw_system)
    {
      draw_system->Draw();
    }
  }
}