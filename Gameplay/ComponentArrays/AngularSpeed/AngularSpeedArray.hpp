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

#include "Objects/Components/ComponentArray.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  //!< Counterclockwise rotation of an object
  struct AngularSpeed
  {
    Radian w_; //!< Counterclockwise rotation speed in radians per tick

    AngularSpeed();

    static void Reflect();
  };

  typedef Barrage::ComponentArrayT<AngularSpeed> AngularSpeedArray;
}

////////////////////////////////////////////////////////////////////////////////
#endif // AngularSpeedArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////