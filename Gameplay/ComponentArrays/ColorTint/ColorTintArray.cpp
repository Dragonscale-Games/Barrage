/* ======================================================================== */
/*!
 * \file            ColorTintArray.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "ColorTintArray.hpp"

namespace Barrage
{
  void ColorTintReflect()
  {
    rttr::registration::class_<ColorTint>("ColorTint")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("red", &ColorTint::red_)
      .property("green", &ColorTint::green_)
      .property("blue", &ColorTint::blue_)
      .property("alpha", &ColorTint::alpha_)
      ;
  }
}