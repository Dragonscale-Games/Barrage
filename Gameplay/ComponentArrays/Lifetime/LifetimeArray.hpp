/* ======================================================================== */
/*!
 * \file            LifetimeArray.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The Lifetime component keeps track of an object's lifetime.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef LifetimeArray_BARRAGE_H
#define LifetimeArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/ComponentArray.hpp"

namespace Barrage
{
  //!< Controls the lifetime of a game object
  struct Lifetime
  {
    long long ticks_; // number of ticks a game object has left to live

    Lifetime();

    static void Reflect();
  };

  typedef Barrage::ComponentArrayT<Lifetime> LifetimeArray;
}

////////////////////////////////////////////////////////////////////////////////
#endif // LifetimeArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////