/* ======================================================================== */
/*!
 * \file            ColorTintArray.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Determines the tint of game objects.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef ColorTintArray_BARRAGE_H
#define ColorTintArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/ComponentArray.hpp"
#include "Renderer/RendererTypes.hpp"

namespace Barrage
{
  typedef Barrage::ComponentArrayT<ColorTint> ColorTintArray;

  void ColorTintReflect();
}

////////////////////////////////////////////////////////////////////////////////
#endif // ColorTintArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////