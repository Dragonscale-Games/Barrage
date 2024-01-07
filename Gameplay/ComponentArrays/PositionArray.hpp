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

#include "Objects/Components/ComponentArray.hpp"
#include "Renderer/RendererTypes.hpp"

namespace Barrage
{
  typedef ComponentArrayT<Position> PositionArray;
}

////////////////////////////////////////////////////////////////////////////////
#endif // PositionArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////