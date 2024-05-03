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
    angle_(Degree(270.0f)),
    speed_(0.0f),
    vx_(0.0f), 
    vy_(0.0f) 
  {
  }

  Velocity::Velocity(float angle, float speed) :
    angle_(angle),
    speed_(speed),
    vx_(speed * glm::cos(angle)),
    vy_(speed * glm::sin(angle))
  {
  }

  Radian Velocity::GetAngle() const
  {
    return angle_;
  }

  float Velocity::GetSpeed() const
  {
    return speed_;
  }

  float Velocity::GetVx() const
  {
    return vx_;
  }

  float Velocity::GetVy() const
  {
    return vy_;
  }

  void Velocity::SetAngle(Radian angle)
  {
    angle_.value_ = ClampWrapped(angle.value_, 0.0f, 2.0f * BARRAGE_PI);

    UpdateCartesianValues();
  }

  void Velocity::SetSpeed(float speed)
  {
    if (speed < 0.0f)
    {
      speed = 0.0f;
    }
    
    speed_ = speed;

    UpdateCartesianValues();
  }

  void Velocity::SetVelocity(float vx, float vy)
  {
    vx_ = vx;
    vy_ = vy;

    UpdatePolarValues();
  }

  void Velocity::SetVx(float vx)
  {
    SetVelocity(vx, vy_);
  }

  void Velocity::SetVy(float vy)
  {
    SetVelocity(vx_, vy);
  }

  void Velocity::Rotate(float angle)
  {
    SetAngle(angle + angle_.value_);
  }

  void Velocity::AddSpeed(float speed)
  {
    SetSpeed(speed + speed_);
  }

  void Velocity::AddVelocity(float vx, float vy)
  {
    SetVelocity(vx_ + vx, vy_ + vy);
  }

  void Velocity::UpdateCartesianValues()
  {
    vx_ = speed_ * glm::cos(angle_.value_);
    vy_ = speed_ * glm::sin(angle_.value_);
  }

  void Velocity::UpdatePolarValues()
  {
    speed_ = glm::length(glm::vec2(vx_, vy_));

    if (glm::abs(vx_) >= MINIMUM_SPEED_THRESHOLD || glm::abs(vy_) >= MINIMUM_SPEED_THRESHOLD)
    {
      angle_ = glm::atan(vy_, vx_);
    }
  }

  void Velocity::Reflect()
  {
    rttr::registration::class_<Velocity>("Velocity")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("angle", &Velocity::GetAngle, &Velocity::SetAngle)
      .property("speed", &Velocity::GetSpeed, &Velocity::SetSpeed)
      .property("vx", &Velocity::GetVx, &Velocity::SetVx)
      .property("vy", &Velocity::GetVy, &Velocity::SetVy)
      ;
  }
}