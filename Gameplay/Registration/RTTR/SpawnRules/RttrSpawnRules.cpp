/* ======================================================================== */
/*!
 * \file            RttrSpawnRules.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   RTTR registration for Spawn Rulles
 */
 /* ======================================================================== */

#include <string>
#include <rttr/registration.h>

#include "SpawnFunctions/Direction/DirectionRules.hpp"
#include "SpawnFunctions/Miscellaneous/MiscellaneousRules.hpp"
#include "SpawnFunctions/Position/PositionRules.hpp"
#include "SpawnFunctions/Speed/SpeedRules.hpp"

namespace Barrage
{
  void ReflectSpawnRules()
  {
    rttr::registration::class_<Spawn::SpawnRingData>("SpawnRingData")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("numObjects", &Spawn::SpawnRingData::numObjects_)
      .property("radius", &Spawn::SpawnRingData::radius_)
      ;

    rttr::registration::class_<Spawn::RandomSpeedData>("RandomSpeedData")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("minSpeed", &Spawn::RandomSpeedData::minSpeed_)
      .property("maxSpeed", &Spawn::RandomSpeedData::maxSpeed_)
      ;

    rttr::registration::class_<Spawn::RotateDirectionData>("RotateDirectionData")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("angle", &Spawn::RotateDirectionData::angle_)
      ;

    rttr::registration::class_<Spawn::SetDirectionData>("SetDirectionData")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("angle", &Spawn::SetDirectionData::angle_)
      ;
  }
}