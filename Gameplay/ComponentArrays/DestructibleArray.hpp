/* ======================================================================== */
/*!
 * \file            DestructibleArray.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The Destructible component keeps track of whether an object is marked
   for destruction.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef DestructibleArray_BARRAGE_H
#define DestructibleArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/ComponentArray.hpp"

namespace Barrage
{
  //!< Keeps track of whether an object is marked for destruction
  struct Destructible
  {
    bool destroyed_; //!< true if marked for destruction

    inline Destructible() : destroyed_(false) {}
  };

  typedef ComponentArrayT<Destructible> DestructibleArray;
}

////////////////////////////////////////////////////////////////////////////////
#endif // DestructibleArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////