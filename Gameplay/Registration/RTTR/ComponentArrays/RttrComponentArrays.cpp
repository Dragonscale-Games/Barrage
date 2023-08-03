/* ======================================================================== */
/*!
 * \file            RttrComponentArrays.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   RTTR registration for component arrays.
 */
 /* ======================================================================== */

#include <string>
#include <rttr/registration.h>

#include "ComponentArrays/AngularSpeedArray.hpp"
#include "ComponentArrays/DestructibleArray.hpp"
#include "ComponentArrays/PositionArray.hpp"
#include "ComponentArrays/RotationArray.hpp"
#include "ComponentArrays/ScaleArray.hpp"
#include "ComponentArrays/SpawnTimerArray.hpp"
#include "ComponentArrays/VelocityArray.hpp"

namespace Barrage
{
  void ReflectComponentArrays()
  {
    rttr::registration::class_<Position>("Position")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("x", &Position::x_)
      .property("y", &Position::y_)
      ;

    rttr::registration::class_<Rotation>("Rotation")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("angle", &Rotation::angle_)
      ;

    rttr::registration::class_<Scale>("Scale")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("w", &Scale::w_)
      .property("h", &Scale::h_)
      ;

    rttr::registration::class_<Scale>("Scale")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("w", &Scale::w_)
      .property("h", &Scale::h_)
      ;

    rttr::registration::class_<Velocity>("Velocity")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("vx", &Velocity::vx_)
      .property("vy", &Velocity::vy_)
      ;
  }
}