/* ======================================================================== */
/*!
 * \file            VelocityArray.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "VelocityArray.hpp"

namespace Barrage
{
  Velocity::Velocity() : 
    vx_(0.0f), vy_(0.0f) 
  {
  }

  void Velocity::Reflect()
  {
    rttr::registration::class_<Velocity>("Velocity")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("vx", &Velocity::vx_)
      .property("vy", &Velocity::vy_)
      ;
  }
}