/* ======================================================================== */
/*!
 * \file            SpawnRuleAllocator.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Interface for allocating any type of spawn rule via its name.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnRuleAllocator_BARRAGE_T
#define SpawnRuleAllocator_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////

#include <type_traits>

namespace Barrage
{
  template <typename T>
  void SpawnRuleAllocator::RegisterSpawnRule(const std::string& name)
  {
    if (spawnRuleAllocMap_.count(name) || !std::is_base_of<SpawnRule, T>::value)
    {
      return;
    }

    spawnRuleAllocMap_[name] = &SpawnRuleAllocator::AllocateSpawnRule<T>;
    spawnRuleNames_.push_back(name);
    spawnRuleNamesSorted_ = false;
  }

  template <typename T>
  std::shared_ptr<SpawnRule> SpawnRuleAllocator::AllocateSpawnRule()
  {
    std::shared_ptr<SpawnRule> newSpawnRule = std::make_shared<T>();

    return newSpawnRule;
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnRuleAllocator_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////