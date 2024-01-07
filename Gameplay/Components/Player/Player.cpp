/* ======================================================================== */
/*!
 * \file            Player.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "Player.hpp"

namespace Barrage
{
  Player::Player() : 
    speedSlow_(3.5f), 
    speedFast_(6.0f), 
    isInvincible_(false), 
    playerHit_(false) 
  {
  }

  void Player::Reflect()
  {
    rttr::registration::class_<Player>("Player")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("speedFast", &Player::speedFast_)
      .property("speedSlow", &Player::speedSlow_)
      .property("isInvincible", &Player::isInvincible_)
      ;
  }
}