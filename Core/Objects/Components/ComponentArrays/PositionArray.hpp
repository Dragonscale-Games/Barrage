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

#include "../BaseClasses/ComponentArray.hpp"

namespace Barrage
{
  //!< World position of an object
  struct Position
  {
    float x_; //!< x coord in world units
    float y_; //!< y coord in world units

    inline Position() : x_(0.0f), y_(0.0f) {}
  };

  typedef ComponentArrayT<Position> PositionArray;

  inline std::string PositionArray::GetClassName() { return "PositionArray"; }
}

////////////////////////////////////////////////////////////////////////////////
#endif // PositionArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////