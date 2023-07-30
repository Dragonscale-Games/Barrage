/* ======================================================================== */
/*!
 * \file            SpawnRuleAllocator.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Interface for allocating any type of spawn rule via its name.
 */
 /* ======================================================================== */

#include "SpawnRuleAllocator.hpp"

namespace Barrage
{
  SpawnRuleAllocMap SpawnRuleAllocator::spawnRuleAllocMap_ = SpawnRuleAllocMap();
  std::vector<std::string> SpawnRuleAllocator::spawnRuleNames_ = std::vector<std::string>();
  bool SpawnRuleAllocator::spawnRuleNamesSorted_ = false;
  
  std::shared_ptr<SpawnRule> SpawnRuleAllocator::CreateSpawnRule(const std::string& name)
  {
    if (spawnRuleAllocMap_.count(name))
    {
      SpawnRuleAllocFunc function = spawnRuleAllocMap_.at(name);
      return function();
    }
    else
    {
      return nullptr;
    }
  }

  const std::vector<std::string>& SpawnRuleAllocator::GetSpawnRuleNames()
  {
    if (!spawnRuleNamesSorted_)
    {
      std::sort(spawnRuleNames_.begin(), spawnRuleNames_.end());
      spawnRuleNamesSorted_ = true;
    }

    return spawnRuleNames_;
  }
}
