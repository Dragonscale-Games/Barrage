/* ======================================================================== */
/*!
 * \file            SystemFactory.tpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Interface for allocating any type of system via its name.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SystemFactory_BARRAGE_T
#define SystemFactory_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////

#include <type_traits>

namespace Barrage
{
  template <typename T>
  void SystemFactory::RegisterSystem(const std::string& name)
  {
    if (systemFactoryMethodMap_.count(name) || !std::is_base_of<System, T>::value)
    {
      return;
    }

    systemNames_.insert(name);
    systemFactoryMethodMap_[name] = &SystemFactory::AllocateSystem<T>;
  }

  template <typename T>
  std::shared_ptr<System> SystemFactory::AllocateSystem(Space& space)
  {
    std::shared_ptr<System> systemPtr = std::make_shared<T>();

    if (systemPtr)
    {
      systemPtr->SetSpace(&space);
    }
    
    return systemPtr;
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SystemFactory_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////