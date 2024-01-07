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

#include "Objects/Components/ComponentArray.hpp"
#include "Renderer/RendererTypes.hpp"

namespace Barrage
{
  typedef ComponentArrayT<Scale> ScaleArray;
}

////////////////////////////////////////////////////////////////////////////////
#endif // ScaleArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////