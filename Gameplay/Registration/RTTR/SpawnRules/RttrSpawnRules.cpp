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

    rttr::registration::class_<Spawn::RandomOffsetData>("RandomOffsetData")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("xVariance", &Spawn::RandomOffsetData::xVariance_)
      .property("yVariance", &Spawn::RandomOffsetData::yVariance_)
      ;

    rttr::registration::class_<Spawn::SpiralData>("SpiralData")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("angleDelta", &Spawn::SpiralData::angleDelta_)
      ;

    rttr::registration::class_<Spawn::MirrorAcrossAxisData>("MirrorAcrossAxisData")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("angle", &Spawn::MirrorAcrossAxisData::angle_)
      ;

    rttr::registration::class_<Spawn::OffsetData>("OffsetData")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("xOffset", &Spawn::OffsetData::xOffset_)
      .property("yOffset", &Spawn::OffsetData::yOffset_)
      ;
  }
}