/* ======================================================================== */
/*!
 * \file            AngularSpeedArray.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The Angular Speed component keeps track of an object's counterclockwise
   rotation speed.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef AngularSpeedArray_BARRAGE_H
#define AngularSpeedArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/ComponentArray.hpp"
#include "Utilities/Utilities.hpp"

namespace Demo
{
  //!< Counterclockwise rotation of an object
  struct AngularSpeed
  {
    Barrage::RADIAN w_; //!< Counterclockwise rotation speed in radians per tick

    inline AngularSpeed() : w_(0.0f) {}
  };

  typedef Barrage::ComponentArrayT<AngularSpeed> AngularSpeedArray;
}

////////////////////////////////////////////////////////////////////////////////
#endif // AngularSpeedArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////