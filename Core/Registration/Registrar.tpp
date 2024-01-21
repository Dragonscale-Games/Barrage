/* ======================================================================== */
/*!
 * \file            Registrar.tpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Handles registration for gameplay code.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Registrar_BARRAGE_T
#define Registrar_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Behavior/BehaviorNodeFactory.hpp"
#include "Objects/Components/ComponentFactory.hpp"
#include "Objects/Spawning/SpawnRuleFactory.hpp"
#include "Objects/Systems/SystemFactory.hpp"

namespace Barrage
{
  template <typename T>
  void Registrar::RegisterBehaviorNode(const std::string& name)
  {
    BehaviorNodeFactory::RegisterBehaviorNode<T>(name);
  }
  
  template <typename T>
  void Registrar::RegisterComponent(const std::string& componentName)
  {
    ComponentFactory::RegisterComponent<T>(componentName);
  }

  template <typename T>
  void Registrar::RegisterComponentArray(const std::string& componentName)
  {
    ComponentFactory::RegisterComponentArray<T>(componentName);
  }
  
  template <typename T>
  void Registrar::RegisterSpawnRule(const std::string& name)
  {
    SpawnRuleFactory::RegisterSpawnRule<T>(name);
  }
  
  template <typename T>
  void Registrar::RegisterSystem(const std::string& name)
  {
    SystemFactory::RegisterSystem<T>(name);
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // Registrar_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////