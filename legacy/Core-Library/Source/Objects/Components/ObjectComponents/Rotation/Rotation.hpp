/* ======================================================================== */
/*!
 * \file            Rotation.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The rotation of an object in radians.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Rotation_BARRAGE_H
#define Rotation_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/ObjectComponent.hpp"

#include <Utilities/Utilities.hpp>

namespace Barrage
{
  //! Component data
  struct RotationData
  {
    RADIAN angle_; //!< Rotation angle in radians
  };

  typedef ObjectComponentDerived<RotationData> Rotation;
}

////////////////////////////////////////////////////////////////////////////////
#endif // Rotation_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////