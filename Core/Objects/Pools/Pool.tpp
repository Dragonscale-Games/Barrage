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
  T* Pool::GetComponentArray(const std::string& componentName)
  {
    return static_cast<T*>(componentArrays_.at(componentName));
  }

  template <typename T>
  T* Pool::GetSharedComponent(const std::string& componentName)
  {
    return static_cast<T*>(sharedComponents_.at(componentName));
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // Pool_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////