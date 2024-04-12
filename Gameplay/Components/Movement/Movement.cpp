/* ======================================================================== */
/*!
 * \file            Movement.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "Movement.hpp"

namespace Barrage
{
  Movement::Movement() :
    curve_()
  {
  }

  void Movement::Reflect()
  {
    rttr::registration::class_<Movement>("Movement")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("curve", &Movement::curve_)
      ;
  }
}