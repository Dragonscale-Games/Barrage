/* ======================================================================== */
/*!
 * \file            TimerSystem.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here>
 */
 /* ======================================================================== */

#include "TimerSystem.hpp"

#include "Objects/Components/GameComponents.hpp"

namespace Barrage
{
  TimerSystem::TimerSystem() :
    System()
  {
    systemComponents_.push_back("Timer");
  }

  void TimerSystem::UpdatePool(Pool* pool)
  {
    Timer* timer = dynamic_cast<Timer*>(pool->poolComponents_.at("Timer"));

    timer->timer_ += 1.0f;
  }
}