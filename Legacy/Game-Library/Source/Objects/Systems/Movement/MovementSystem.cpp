/* ======================================================================== */
/*!
 * \file            MovementSystem.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here>
 */
 /* ======================================================================== */

#include "MovementSystem.hpp"

#include "Objects/Components/GameComponents.hpp"

namespace Barrage
{
  MovementSystem::MovementSystem() :
    System()
  {
    systemComponents_.push_back("Position");
    systemComponents_.push_back("Velocity");
  }

  void MovementSystem::UpdatePool(Pool* pool)
  {
    Position* positions = static_cast<Position*>(pool->objectComponents_.at("Position"));
    Velocity* velocities = static_cast<Velocity*>(pool->objectComponents_.at("Velocity"));

    unsigned num_objects = pool->activeObjects_;

    for (unsigned i = 0; i < num_objects; ++i)
    {
      positions->data_[i].position_ += velocities->data_[i].velocity_;
    }
  }
}