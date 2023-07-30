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
#include "Spaces/Space.hpp"

#include "Objects/Systems/DrawSystem.hpp"

namespace Barrage
{
  ObjectManager::ObjectManager(Space& space) :
    poolManager_(space),
    systemManager_()
  {
    RegisterSystem<DrawSystem>("DrawSystem");

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

  std::vector<std::string_view> ObjectManager::GetRegisteredSystemNames()
  {
    return systemManager_.GetRegisteredSystemNames();
  }

  std::vector<std::string_view> ObjectManager::GetSystemUpdateOrder()
  {
    return systemManager_.GetSystemUpdateOrder();
  }

  void ObjectManager::SubscribePools()
  {
    std::vector<std::string> poolNames = poolManager_.GetPoolNames();
    
    for (auto it = poolNames.begin(); it != poolNames.end(); ++it)
    {
      Pool* pool = poolManager_.GetPool(*it);
      systemManager_.Subscribe(pool);
    }
    
  }

  void ObjectManager::CreatePool(const PoolArchetype& archetype)
  {
    poolManager_.CreatePool(archetype);
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
}