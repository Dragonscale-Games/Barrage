/* ======================================================================== */
/*!
 * \file            TextureUVArray.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "TextureUVArray.hpp"

namespace Barrage
{
  void TextureUVReflect()
  {
    rttr::registration::class_<TextureUV>("TextureUV")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("uMin", &TextureUV::uMin_)
      .property("vMin", &TextureUV::vMin_)
      .property("uSize", &TextureUV::uSize_)
      .property("vSize", &TextureUV::vSize_)
      ;
  }
}