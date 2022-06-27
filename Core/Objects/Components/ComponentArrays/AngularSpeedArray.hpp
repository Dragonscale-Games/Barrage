/* ======================================================================== */
/*!
 * \file            AngularSpeed.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The Angular Speed component keeps track of an object's counterclockwise
   rotation speed.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef AngularSpeed_BARRAGE_H
#define AngularSpeed_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "../BaseClasses/ComponentArray.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  //!< Counterclockwise rotation of an object
  struct AngularSpeed
  {
    RADIAN w_; //!< Counterclockwise rotation speed in radians per tick

    inline AngularSpeed() : w_(0.0f) {}
  };

  typedef ComponentArrayT<AngularSpeed> AngularSpeedArray;

  inline std::string AngularSpeedArray::GetClassName() { return "AngularSpeedArray"; }
}

////////////////////////////////////////////////////////////////////////////////
#endif // AngularSpeed_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////