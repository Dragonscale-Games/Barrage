/* ======================================================================== */
/*!
 * \file            SpawnRuleFactory.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Interface for allocating any type of spawn rule via its name.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "SpawnRuleFactory.hpp"

namespace Barrage
{
  SpawnRuleFactoryMethodMap SpawnRuleFactory::spawnRuleFactoryMethodMap_ = SpawnRuleFactoryMethodMap();
  StringSet SpawnRuleFactory::spawnRuleNames_ = StringSet();

  SpawnRuleDeepPtr SpawnRuleFactory::CreateSpawnRule(const std::string& name)
  {
    if (spawnRuleFactoryMethodMap_.count(name))
    {
      SpawnRuleFactoryMethod function = spawnRuleFactoryMethodMap_.at(name);
      return function();
    }
    else
    {
      return nullptr;
    }
  }

  const StringSet& SpawnRuleFactory::GetSpawnRuleNames()
  {
    return spawnRuleNames_;
  }
}
