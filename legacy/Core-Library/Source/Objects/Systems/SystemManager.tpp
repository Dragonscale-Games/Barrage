/* ======================================================================== */
/*!
 * \file            SystemManager.tpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef SystemManager_BARRAGE_T
#define SystemManager_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
  template <typename T>
  void SystemManager::RegisterSystem(const std::string& systemName)
  {
    if (systems_.find(systemName) != systems_.end())
    {
      return;
    }
    
    T* new_system_specialized = new T;
    System* new_system = dynamic_cast<System*>(new_system_specialized);

    if (new_system)
    {
      systems_[systemName] = new_system;
      systemNames_.push_back(systemName);
      updateOrderList_.push_back(systemName);
    }
    else
    {
      delete new_system_specialized;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SystemManager_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////