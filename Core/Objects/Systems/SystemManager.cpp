/* ======================================================================== */
/*!
 * \file            SystemManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 
 */
/* ======================================================================== */

#include "stdafx.h"
#include "SystemManager.hpp"

namespace Barrage
{
  SystemManager::SystemManager() :
    systems_(),
    systemNames_(),
    updateOrderList_()
  {
  }

  SystemManager::~SystemManager()
  {
    for (auto it = systems_.begin(); it != systems_.end(); ++it)
    {
      delete it->second;
    }
  }

  void SystemManager::SetUpdateOrder(const std::vector<std::string_view>& updateOrderList)
  {
    updateOrderList_ = updateOrderList;
  }

  void SystemManager::Subscribe(Pool* pool)
  {
    if (pool)
    {
      for (auto it = systems_.begin(); it != systems_.end(); ++it)
      {
        System* system = it->second;

        system->Subscribe(pool);
      }
    }
  }

  void SystemManager::Unsubscribe(Pool* pool)
  {
    for (auto it = systems_.begin(); it != systems_.end(); ++it)
    {
      System* system = it->second;

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

  System* SystemManager::GetSystem(const std::string_view& name)
  {
    if (systems_.find(name) != systems_.end())
      return systems_.at(name);
    else
      return nullptr;
  }

  std::vector<std::string_view> SystemManager::GetRegisteredSystemNames()
  {
    return systemNames_;
  }

  std::vector<std::string_view> SystemManager::GetSystemUpdateOrder()
  {
    return updateOrderList_;
  }
}