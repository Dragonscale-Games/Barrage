/* ======================================================================== */
/*!
 * \file            ScaleArray.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "ScaleArray.hpp"

namespace Barrage
{
  void ScaleReflect()
  {
    rttr::registration::class_<Scale>("Scale")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("w", &Scale::w_)
      .property("h", &Scale::h_)
      ;
  }
}