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
#include "Engine/Engine.hpp"
#include "Utilities/Utilities.hpp"
#include "Source/Components/DemoComponents.hpp"

namespace Demo
{
  using namespace Barrage;
  
  static const unsigned BASIC_MOVEMENT_POOLS = 0;
  static const unsigned BASIC_ROTATION_POOLS = 1;
  static const unsigned PLAYER_POOLS = 2;
  static const unsigned BOUNDED_PLAYER_POOLS = 3;
  
  MovementSystem::MovementSystem() :
    System()
  {
    PoolType basic_movement_type;
    basic_movement_type.AddComponentName("PositionArray");
    basic_movement_type.AddComponentName("VelocityArray");
    poolTypes_[BASIC_MOVEMENT_POOLS] = basic_movement_type;

    PoolType basic_rotation_type;
    basic_rotation_type.AddComponentName("RotationArray");
    basic_rotation_type.AddComponentName("AngularSpeedArray");
    poolTypes_[BASIC_ROTATION_POOLS] = basic_rotation_type;

    PoolType player_type;
    player_type.AddComponentName("PositionArray");
    player_type.AddComponentName("Player");
    poolTypes_[PLAYER_POOLS] = player_type;

    PoolType bounded_player_type;
    bounded_player_type.AddComponentName("PositionArray");
    bounded_player_type.AddComponentName("BoundaryBox");
    bounded_player_type.AddComponentName("Player");
    poolTypes_[BOUNDED_PLAYER_POOLS] = bounded_player_type;
  }

  void MovementSystem::Update()
  {
    UpdatePoolGroup(PLAYER_POOLS, UpdatePlayerMovement);
    UpdatePoolGroup(BOUNDED_PLAYER_POOLS, UpdatePlayerBounds);
    UpdatePoolGroup(BASIC_MOVEMENT_POOLS, UpdateBasicMovement);
    UpdatePoolGroup(BASIC_ROTATION_POOLS, UpdateBasicRotation);
  }

  void MovementSystem::UpdatePlayerMovement(Pool* pool)
  {
    Player& player = *pool->GetSharedComponent<Player>("Player");

    float speed = 0.0f;
    Velocity player_velocity;

    if (Engine::Instance->Input().KeyIsDown(KEY_SHIFT_LEFT))
    {
      speed = player.speedSlow_;
    }
    else
    {
      speed = player.speedFast_;
    }

    if (Engine::Instance->Input().KeyIsDown(KEY_LEFT))
      player_velocity.vx_ = -speed;
    else if (Engine::Instance->Input().KeyIsDown(KEY_RIGHT))
      player_velocity.vx_ = speed;
    else
      player_velocity.vx_ = 0.0f;

    if (Engine::Instance->Input().KeyIsDown(KEY_UP))
      player_velocity.vy_ = speed;
    else if (Engine::Instance->Input().KeyIsDown(KEY_DOWN))
      player_velocity.vy_ = -speed;
    else
      player_velocity.vy_ = 0.0f;

    if (player_velocity.vx_ && player_velocity.vy_)
    {
      player_velocity.vx_ = player_velocity.vx_ / 1.4142f;
      player_velocity.vy_ = player_velocity.vy_ / 1.4142f;
    }

    PositionArray& position_array = *pool->GetComponentArray<PositionArray>("PositionArray");

    unsigned num_objects = pool->numActiveObjects_;

    for (unsigned i = 0; i < num_objects; ++i)
    {
      position_array.Data(i).x_ += player_velocity.vx_;
      position_array.Data(i).y_ += player_velocity.vy_;
    }
  }

  void MovementSystem::UpdatePlayerBounds(Pool* pool)
  {
    PositionArray& position_array = *pool->GetComponentArray<PositionArray>("PositionArray");
    BoundaryBox& bounds = *pool->GetSharedComponent<BoundaryBox>("BoundaryBox");

    unsigned num_objects = pool->numActiveObjects_;

    for (unsigned i = 0; i < num_objects; ++i)
    {
      Position& pos = position_array.Data(i);

      if (pos.x_ < bounds.xMin_)
        pos.x_ = bounds.xMin_;
      else if (pos.x_ > bounds.xMax_)
        pos.x_ = bounds.xMax_;

      if (pos.y_ < bounds.yMin_)
        pos.y_ = bounds.yMin_;
      else if (pos.y_ > bounds.yMax_)
        pos.y_ = bounds.yMax_;
    }
  }

  void MovementSystem::UpdateBasicMovement(Pool* pool)
  {
    PositionArray& position_array = *pool->GetComponentArray<PositionArray>("PositionArray");
    VelocityArray& velocity_array = *pool->GetComponentArray<VelocityArray>("VelocityArray");

    unsigned num_objects = pool->numActiveObjects_;

    for (unsigned i = 0; i < num_objects; ++i)
    {
      position_array.Data(i).x_ += velocity_array.Data(i).vx_;
      position_array.Data(i).y_ += velocity_array.Data(i).vy_;
    }
  }

  void MovementSystem::UpdateBasicRotation(Pool* pool)
  {
    RotationArray& rotation_array = *pool->GetComponentArray<RotationArray>("RotationArray");
    AngularSpeedArray& angular_speed_array = *pool->GetComponentArray<AngularSpeedArray>("AngularSpeedArray");

    unsigned num_objects = pool->numActiveObjects_;

    for (unsigned i = 0; i < num_objects; ++i)
    {
      rotation_array.Data(i).angle_ += angular_speed_array.Data(i).w_;
      rotation_array.Data(i).angle_ = ClampWrapped(rotation_array.Data(i).angle_, 0.0f, 2.0f * 3.141592f);
    }
  }
}