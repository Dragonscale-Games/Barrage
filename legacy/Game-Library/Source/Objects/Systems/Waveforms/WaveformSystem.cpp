/* ======================================================================== */
/*!
 * \file            WaveformSystem.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 
 */
/* ======================================================================== */

#include "WaveformSystem.hpp"
#include "Objects/Components/GameComponents.hpp"

namespace Barrage
{
  WaveformSystem::WaveformSystem() :
    System()
  {
    systemComponents_.push_back("Tags");
    systemComponents_.push_back("Position");
    systemComponents_.push_back("Timer");
  }
  
  void WaveformSystem::Subscribe(Pool* pool)
  {
    if (PoolMatchesSystem(pool))
    {
      Tags* pool_tags = static_cast<Tags*>(pool->poolComponents_["Tags"]);

      if (pool_tags->HasTag("WaveDot"))
      {
        pools_.insert(std::pair<unsigned, Pool*>(0, pool));
      }
    }
  }

  void WaveformSystem::UpdatePool(Pool* pool)
  {
    Position* positions = static_cast<Position*>(pool->objectComponents_["Position"]);
    Timer* timer = static_cast<Timer*>(pool->poolComponents_["Timer"]);

    float a = 100.0f;
    float k = 0.05f;
    float w = 0.01f;
    float t = timer->timer_;

    for (unsigned i = 0; i < pool->activeObjects_; ++i)
    {
      glm::vec2& pos = positions->data_[i].position_;
      pos.y = 360.0f + a * glm::sin(k * pos.x + w * t) + a * glm::sin(1.5f * k * pos.x + 1.1f * w * t);
    }
  }
}