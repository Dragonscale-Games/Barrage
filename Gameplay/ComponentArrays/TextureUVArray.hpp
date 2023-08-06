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

namespace Barrage
{
  //!< Texture coordinates
  struct TextureUV
  {
    float uMin_;
    float vMin_;
    float uSize_;
    float vSize_;

    inline TextureUV() : uMin_(0.0f), vMin_(0.0f), uSize_(1.0f), vSize_(1.0f) {}
  };

  typedef Barrage::ComponentArrayT<TextureUV> TextureUVArray;
}

////////////////////////////////////////////////////////////////////////////////
#endif // TextureUVArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////