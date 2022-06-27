/* ======================================================================== */
/*!
 * \file            SpawnFuncManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Keeps track of object initialization functions and their names.
 */
/* ======================================================================== */

#include "stdafx.h"
#include "SpawnFuncManager.hpp"
#include "Objects/Pools/Pool.hpp"

namespace Barrage
{
  SpawnFuncManager::SpawnFuncManager() :
    spawnFuncs_(),
    spawnFuncNames_()
  {
  }

  void SpawnFuncManager::RegisterSpawnFunc(const std::string name, SpawnFunc spawnFunction)
  {
    if (spawnFuncs_.find(name) != spawnFuncs_.end())
    {
      return;
    }

    if (spawnFunction == nullptr)
    {
      return;
    }

    spawnFuncs_[name] = spawnFunction;
    spawnFuncNames_.push_back(name);
  }

  SpawnFunc SpawnFuncManager::GetSpawnFunc(const std::string name)
  {
    if (spawnFuncs_.find(name) != spawnFuncs_.end())
    {
      return spawnFuncs_.at(name);
    }
    else
    {
      return nullptr;
    }
  }

  std::vector<std::string> SpawnFuncManager::GetSpawnFuncNames()
  {
    return spawnFuncNames_;
  }
}