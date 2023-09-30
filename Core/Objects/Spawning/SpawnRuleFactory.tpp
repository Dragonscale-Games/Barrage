/* ======================================================================== */
/*!
 * \file            SpawnRuleFactory.tpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Interface for allocating any type of spawn rule via its name.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnRuleFactory_BARRAGE_T
#define SpawnRuleFactory_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////

#include <type_traits>

namespace Barrage
{
  template <typename T>
  void SpawnRuleFactory::RegisterSpawnRule(const std::string& name)
  {
    if (spawnRuleFactoryMethodMap_.count(name) || !std::is_base_of<SpawnRule, T>::value)
    {
      return;
    }

    spawnRuleNames_.insert(name);
    spawnRuleFactoryMethodMap_[name] = &SpawnRuleFactory::AllocateSpawnRule<T>;
  }

  template <typename T>
  SpawnRulePtr SpawnRuleFactory::AllocateSpawnRule()
  {
    return SpawnRulePtr(std::make_shared<T>());
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnRuleFactory_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////