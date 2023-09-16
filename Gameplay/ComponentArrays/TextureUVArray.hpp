/* ======================================================================== */
/*!
 * \file            TextureUVArray.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Texture coordinates (UVs).
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef TextureUVArray_BARRAGE_H
#define TextureUVArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/ComponentArray.hpp"
#include "Renderer/RendererTypes.hpp"

namespace Barrage
{
  typedef Barrage::ComponentArrayT<TextureUV> TextureUVArray;
}

////////////////////////////////////////////////////////////////////////////////
#endif // TextureUVArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////