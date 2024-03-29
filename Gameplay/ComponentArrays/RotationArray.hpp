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

#include "Objects/Components/BaseClasses/ComponentArray.hpp"
#include "Renderer/RendererTypes.hpp"

namespace Barrage
{
  typedef ComponentArrayT<Rotation> RotationArray;
}

////////////////////////////////////////////////////////////////////////////////
#endif // RotationArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////