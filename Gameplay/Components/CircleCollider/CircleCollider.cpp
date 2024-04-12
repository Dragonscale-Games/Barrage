/* ======================================================================== */
/*!
 * \file            CircleCollider.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "CircleCollider.hpp"

namespace Barrage
{
  CircleCollider::CircleCollider() : 
    radius_(32.0f) 
  {
  }

  void CircleCollider::Reflect()
  {
    rttr::registration::class_<CircleCollider>("CircleCollider")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("radius", &CircleCollider::radius_)
      ;
  }
}