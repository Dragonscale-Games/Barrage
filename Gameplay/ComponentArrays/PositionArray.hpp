/* ======================================================================== */
/*!
 * \file            PositionArray.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The Position component keeps track of an object's world position.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef PositionArray_BARRAGE_H
#define PositionArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/ComponentArray.hpp"

namespace Barrage
{
  //!< World position of an object
  struct Position
  {
    float x_; //!< x coord in world units
    float y_; //!< y coord in world units

    inline Position() : x_(960.0f), y_(540.0f) {}
  };

  typedef ComponentArrayT<Position> PositionArray;
}

////////////////////////////////////////////////////////////////////////////////
#endif // PositionArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////