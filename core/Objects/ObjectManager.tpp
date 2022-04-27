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

namespace Barrage
{
  template <typename T>
  void ObjectManager::RegisterComponent(const std::string& componentName)
  {
    componentAllocator_.RegisterComponent<T>(componentName);
  }

  template <typename T>
  void ObjectManager::RegisterSystem(const std::string& systemName)
  {
    systemManager_.RegisterSystem<T>(systemName);
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // ObjectManager_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////