/* ======================================================================== */
/*!
 * \file            PositionArray.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "PositionArray.hpp"

namespace Barrage
{
  void PositionReflect()
  {
    rttr::registration::class_<Position>("Position")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("x", &Position::x_)
      .property("y", &Position::y_)
      ;
  }
}