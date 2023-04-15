/* ======================================================================== */
/*!
 * \file            SpawnFunctionManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Keeps track of spawn functions and their names.
 */
/* ======================================================================== */

#include "stdafx.h"
#include "SpawnFunctionManager.hpp"
#include "Objects/Pools/Pool.hpp"

namespace Barrage
{
  SpawnFunctionMap SpawnFunctionManager::spawnFunctions_ = SpawnFunctionMap();
  std::vector<std::string_view> SpawnFunctionManager::spawnFunctionNames_ = std::vector<std::string_view>(); 
  
  void SpawnFunctionManager::RegisterSpawnFunction(const std::string_view& name, SpawnFunction spawnFunction)
  {
    if (spawnFunctions_.count(name))
    {
      return;
    }

    if (spawnFunction == nullptr)
    {
      return;
    }

    spawnFunctions_[name] = spawnFunction;
    spawnFunctionNames_.push_back(name);
  }

  SpawnFunction SpawnFunctionManager::GetSpawnFunction(const std::string_view& name)
  {
    if (spawnFunctions_.find(name) != spawnFunctions_.end())
    {
      return spawnFunctions_.at(name);
    }
    else
    {
      return nullptr;
    }
  }

  std::vector<std::string_view> SpawnFunctionManager::GetSpawnFunctionNames()
  {
    return spawnFunctionNames_;
  }
}