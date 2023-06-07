/* ======================================================================== */
/*!
 * \file            ObjectManager.tpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The main point of contact for game object manipulation in the engine.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef ObjectManager_BARRAGE_T
#define ObjectManager_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////

#include "Components/ComponentAllocator.hpp"

namespace Barrage
{
  template <typename T>
  void ObjectManager::RegisterComponent(const std::string_view& componentName)
  {
    ComponentAllocator::RegisterComponent<T>(componentName);
  }
  
  template <typename T>
  void ObjectManager::RegisterComponentArray(const std::string_view& componentName)
  {
    ComponentAllocator::RegisterComponentArray<T>(componentName);
  }

  template <typename T>
  void ObjectManager::RegisterSystem(const std::string_view& systemName)
  {
    systemManager_.RegisterSystem<T>(systemName);
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // ObjectManager_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////