/* ======================================================================== */
/*!
 * \file            SpawnTimerArray.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "SpawnTimerArray.hpp"

namespace Barrage
{
  SpawnTimer::SpawnTimer() :
    ticks_(0)
  {
  }
  
  void SpawnTimer::Reflect()
  {
    rttr::registration::class_<SpawnTimer>("SpawnTimer")
      .constructor<>() (rttr::policy::ctor::as_object)
      ;
  }
}