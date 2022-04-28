/* ======================================================================== */
/*!
 * \file            AngularSpeed.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Angular speed in radians per tick.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef AngularSpeed_BARRAGE_H
#define AngularSpeed_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/ObjectComponent.hpp"

#include <Utilities/Utilities.hpp>

namespace Barrage
{
  //! Component data
  struct AngularSpeedData
  {
    RADIAN vw_; //!< Angular speed in radians per tick
  };

  typedef ObjectComponentDerived<AngularSpeedData> AngularSpeed;
}

////////////////////////////////////////////////////////////////////////////////
#endif // AngularSpeed_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////