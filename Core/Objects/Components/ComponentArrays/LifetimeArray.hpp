/* ======================================================================== */
/*!
 * \file            LifetimeArray.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 

 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef LifetimeArray_BARRAGE_H
#define LifetimeArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "../BaseClasses/ComponentArray.hpp"

namespace Barrage
{
  //!< Destroys an object after a certain number of ticks
  struct Lifetime
  {
    unsigned ticks_; //!< the number of ticks the object has left to live

    inline Lifetime() : ticks_(60) {}
  };

  typedef ComponentArrayT<Lifetime> LifetimeArray;

  inline std::string LifetimeArray::GetClassName() { return "LifetimeArray"; }
}

////////////////////////////////////////////////////////////////////////////////
#endif // LifetimeArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////