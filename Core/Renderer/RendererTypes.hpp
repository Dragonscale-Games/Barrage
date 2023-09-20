/* ======================================================================== */
/*!
 * \file            RendererTypes.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Simple types used by the renderer.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef RendererTypes_BARRAGE_H
#define RendererTypes_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Utilities/Utilities.hpp"

namespace Barrage
{
  struct Position
  {
    float x_;
    float y_;

    inline Position() : x_(960.0f), y_(540.0f) {}
  };

  struct Rotation
  {
    Radian angle_;

    inline Rotation() : angle_(0.0f) {}
  };

  struct Scale
  {
    float w_;
    float h_;

    inline Scale() : w_(100.0f), h_(100.0f) {}
  };

  struct ColorTint
  {
    float red_;
    float green_;
    float blue_;
    float alpha_;

    inline ColorTint() : red_(0.0f), green_(0.0f), blue_(0.0f), alpha_(1.0f) {}
  };

  struct TextureUV
  {
    float uMin_;
    float vMin_;
    float uSize_;
    float vSize_;

    inline TextureUV() : uMin_(0.0f), vMin_(0.0f), uSize_(1.0f), vSize_(1.0f) {}
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // RendererTypes_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////