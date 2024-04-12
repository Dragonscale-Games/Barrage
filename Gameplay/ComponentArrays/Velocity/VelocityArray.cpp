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
#include "glm/glm.hpp"

namespace Barrage
{
  Velocity::Velocity() : 
    vx_(0.0f), 
    vy_(-MINIMUM_SPEED) 
  {
  }

  Velocity::Velocity(float vx, float vy) :
    vx_(vx),
    vy_(vy)
  {
    if (glm::length(glm::vec2(vx, vy)) < MINIMUM_SPEED)
    {
      vx_ = 0.0f;
      vy_ = -MINIMUM_SPEED;
    }
  }

  void Velocity::Rotate(float cosAngle, float sinAngle)
  {
    glm::vec2 rvel(vx_, vy_);

    rvel.x =  vx_ * cosAngle + vy_ * sinAngle;
    rvel.y = -vx_ * sinAngle + vy_ * cosAngle;

    vx_ = rvel.x;
    vy_ = rvel.y;
  }

  void Velocity::SetSpeed(float speed)
  {
    glm::vec2 velocity(vx_, vy_);
    glm::vec2 direction = glm::normalize(velocity);
    velocity = speed * direction;

    vx_ = velocity.x;
    vy_ = velocity.y;
  }

  float Velocity::GetAngle()
  {
    return glm::atan(-vx_, -vy_);
  }

  void Velocity::Reflect()
  {
    rttr::registration::class_<Velocity>("Velocity")
      .constructor<>() (rttr::policy::ctor::as_object)
      ;
  }
}