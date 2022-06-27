/* ======================================================================== */
/*!
 * \file            RotationArray.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The Rotation component keeps track of the counterclockwise rotation of
   an object in radians.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef RotationArray_BARRAGE_H
#define RotationArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "../BaseClasses/ComponentArray.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  //!< Counterclockwise rotation of an object
  struct Rotation
  {
    RADIAN angle_; //!< Rotation angle in radians

    inline Rotation() : angle_(0.0f) {}
  };

  typedef ComponentArrayT<Rotation> RotationArray;

  inline std::string RotationArray::GetClassName() { return "RotationArray"; }
}

////////////////////////////////////////////////////////////////////////////////
#endif // RotationArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////