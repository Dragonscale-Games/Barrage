/* ======================================================================== */
/*!
 * \file            Sprite.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Information used to texture and draw an object.
 */
 /* ======================================================================== */

#include "Sprite.hpp"

namespace Barrage
{
  Sprite::Sprite() : texture_("<default>"), layer_(0)
  {
  }

  void Sprite::Reflect()
  {
    rttr::registration::class_<Sprite>("Sprite")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("texture", &Sprite::texture_)
      .property("layer", &Sprite::layer_)
      ;
  }
}