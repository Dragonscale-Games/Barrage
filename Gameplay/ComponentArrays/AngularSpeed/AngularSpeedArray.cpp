/* ======================================================================== */
/*!
 * \file            AngularSpeedArray.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "AngularSpeedArray.hpp"

namespace Barrage
{
  AngularSpeed::AngularSpeed() :
    w_(0.0f) 
  {
  }
  
  void AngularSpeed::Reflect()
  {
    rttr::registration::class_<AngularSpeed>("AngularSpeed")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("w", &AngularSpeed::w_)
      ;
  }
}