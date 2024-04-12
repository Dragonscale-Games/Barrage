/* ======================================================================== */
/*!
 * \file            RotationArray.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "RotationArray.hpp"

namespace Barrage
{
  void RotationReflect()
  {
    rttr::registration::class_<Rotation>("Rotation")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("angle", &Rotation::angle_)
      ;
  }
}