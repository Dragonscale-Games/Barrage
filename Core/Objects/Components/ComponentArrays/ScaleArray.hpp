/* ======================================================================== */
/*!
 * \file            ScaleArray.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The Scale component keeps track of the world dimensions of a game object.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef ScaleArray_BARRAGE_H
#define ScaleArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "../BaseClasses/ComponentArray.hpp"

namespace Barrage
{
  //!< World dimensions of an object
  struct Scale
  {
    float w_; //!< width in world units
    float h_; //!< height in world units

    inline Scale() : w_(100.0f), h_(100.0f) {}
  };

  typedef ComponentArrayT<Scale> ScaleArray;

  inline std::string ScaleArray::GetClassName() { return "ScaleArray"; }
}

////////////////////////////////////////////////////////////////////////////////
#endif // ScaleArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////