/* ======================================================================== */
/*!
 * \file            SystemManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   In charge of holding systems and calling their update functions.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "SystemManager.hpp"

namespace Barrage
{
  SystemManager::SystemManager(Space& space) :
    space_(space),
    systems_(),
    updateOrderList_()
  {
  }

  void SystemManager::Subscribe(Pool* pool)
  {
    if (pool)
    {
      for (auto it = systems_.begin(); it != systems_.end(); ++it)
      {
        std::shared_ptr<System> system = it->second;

        system->Subscribe(pool);
      }
    }
  }

  void SystemManager::Unsubscribe(Pool* pool)
  {
    for (auto it = systems_.begin(); it != systems_.end(); ++it)
    {
      std::shared_ptr<System> system = it->second;

      system->Unsubscribe(pool);
    }
  }

  void SystemManager::Update()
  {
    for (auto it = updateOrderList_.begin(); it != updateOrderList_.end(); ++it)
    {
      if (systems_.find(*it) != systems_.end())
      {
        systems_.at(*it)->Update();
      }
    }
  }

  std::shared_ptr<System> SystemManager::GetSystem(const std::string& name)
  {
    if (systems_.find(name) != systems_.end())
      return systems_.at(name);
    else
      return nullptr;
  }

  const std::vector<std::string>& SystemManager::GetSystemUpdateOrder() const
  {
    return updateOrderList_;
  }

  void SystemManager::SetUpdateOrder(const std::vector<std::string>& updateOrderList)
  {
    updateOrderList_ = updateOrderList;
  }
}