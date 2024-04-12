/* ======================================================================== */
/*!
 * \file            ComponentAllocator.tpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Interface for allocating any type of component via its name.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Pool_BARRAGE_T
#define Pool_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

namespace Barrage
{
  template <typename T>
  ComponentT<T>& Pool::GetComponent(const std::string& componentName)
  {
    return static_cast<ComponentT<T>&>(*components_.at(componentName));
  }

  template <typename T>
  ComponentArrayT<T>& Pool::GetComponentArray(const std::string& componentArrayName)
  {
    return static_cast<ComponentArrayT<T>&>(*componentArrays_.at(componentArrayName));
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // Pool_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////