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

#include "Objects/Components/ComponentArray.hpp"

namespace Barrage
{
  typedef ComponentArrayT<Destructible> DestructibleArray;
}

////////////////////////////////////////////////////////////////////////////////
#endif // DestructibleArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////