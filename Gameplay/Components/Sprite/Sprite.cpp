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
  Sprite::Sprite() : 
    texture_("<default>"), 
    layer_(0),
    cols_(1),
    rows_(1)
  {
  }

  void Sprite::Reflect()
  {
    rttr::registration::class_<Sprite>("Sprite")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("texture", &Sprite::texture_)
      .property("layer", &Sprite::layer_)
      .property("cols", &Sprite::cols_)
      .property("rows", &Sprite::rows_)
      ;
  }
}