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

namespace Barrage
{
  template <typename T>
  ComponentArrayT<T>* Pool::GetComponentArray(const std::string_view& componentName)
  {
    return dynamic_cast<ComponentArrayT<T>*>(componentArrays_.at(componentName));
  }

  template <typename T>
  SharedComponentT<T>* Pool::GetSharedComponent(const std::string_view& componentName)
  {
    return dynamic_cast<SharedComponentT<T>*>(sharedComponents_.at(componentName));
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // Pool_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////