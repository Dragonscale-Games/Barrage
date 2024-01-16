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
#include "glm/glm.hpp"

namespace Barrage
{
  struct Position
  {
    float x_;
    float y_;

    inline Position() : x_(0.0f), y_(0.0f) {}

    inline void Rotate(float cosAngle, float sinAngle)
    {
      glm::vec2 rpos(x_, y_);

      rpos.x =  x_ * cosAngle + y_ * sinAngle;
      rpos.y = -x_ * sinAngle + y_ * cosAngle;

      x_ = rpos.x;
      y_ = rpos.y;
    }
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

    inline Scale() : w_(64.0f), h_(64.0f) {}
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