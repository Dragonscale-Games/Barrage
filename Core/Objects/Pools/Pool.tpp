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
  ComponentT<T>& Pool::GetComponent(std::string_view componentName)
  {
    
  }

  template <typename T>
  ComponentArrayT<T>& Pool::GetComponentArray(std::string_view componentName)
  {
    
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // Pool_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////