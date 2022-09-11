/* ======================================================================== */
/*!
 * \file            CollisionSystem.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here>
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "CollisionSystem.hpp"

namespace Barrage
{
  static const unsigned CIRCLE_BULLET_POOLS = 0;
  static const unsigned CIRCLE_PLAYER_POOLS = 1;
  static const unsigned BOUNDED_BULLET_POOLS = 2;
  
  CollisionSystem::CollisionSystem() :
    System()
  {
    PoolType circle_bullet_type;
    circle_bullet_type.AddComponentName("CircleCollider");
    circle_bullet_type.AddComponentName("PositionArray");
    circle_bullet_type.AddComponentName("DestructibleArray");
    circle_bullet_type.AddTag("Bullet");
    poolTypes_[CIRCLE_BULLET_POOLS] = circle_bullet_type;

    PoolType bounded_bullet_type;
    bounded_bullet_type.AddComponentName("PositionArray");
    bounded_bullet_type.AddComponentName("BoundaryBox");
    bounded_bullet_type.AddComponentName("DestructibleArray");
    bounded_bullet_type.AddTag("Bullet");
    poolTypes_[BOUNDED_BULLET_POOLS] = bounded_bullet_type;

    PoolType circle_player_type;
    circle_player_type.AddComponentName("CircleCollider");
    circle_player_type.AddComponentName("PositionArray");
    circle_player_type.AddTag("Player");
    poolTypes_[CIRCLE_PLAYER_POOLS] = circle_player_type;
  }

  void CollisionSystem::Update()
  {
    UpdatePoolGroup(BOUNDED_BULLET_POOLS, UpdateBoundedBullets);
    
    UpdateInteraction(CIRCLE_PLAYER_POOLS, CIRCLE_BULLET_POOLS, UpdatePlayerBulletCollisions);
  }

  void CollisionSystem::UpdateBoundedBullets(Pool* pool)
  {
    PositionArray& position_array = *pool->GetComponentArray<PositionArray>("PositionArray");
    DestructibleArray& destructible_array = *pool->GetComponentArray<DestructibleArray>("DestructibleArray");

    BoundaryBox& boundary_box = *pool->GetSharedComponent<BoundaryBox>("BoundaryBox");

    unsigned num_bullets = pool->size_;

    for (unsigned i = 0; i < num_bullets; ++i)
    {
      Position& pos = position_array[i];

      if (pos.x_ < boundary_box.xMin_ || pos.x_ > boundary_box.xMax_ || pos.y_ < boundary_box.yMin_ || pos.y_ > boundary_box.yMax_)
      {
        destructible_array[i].destroyed_ = true;
      }
    }
  }

  void CollisionSystem::UpdatePlayerBulletCollisions(Pool* player_pool, Pool* bullet_pool)
  {
    CircleCollider& player_collider = *player_pool->GetSharedComponent<CircleCollider>("CircleCollider");
    CircleCollider& bullet_collider = *bullet_pool->GetSharedComponent<CircleCollider>("CircleCollider");

    PositionArray& player_positions = *player_pool->GetComponentArray<PositionArray>("PositionArray");
    PositionArray& bullet_positions = *bullet_pool->GetComponentArray<PositionArray>("PositionArray");

    DestructibleArray& bullet_destructibles = *bullet_pool->GetComponentArray<DestructibleArray>("DestructibleArray");

    float collision_radius = player_collider.radius_ + bullet_collider.radius_;

    unsigned num_players = player_pool->size_;
    unsigned num_bullets = bullet_pool->size_;

    for (unsigned i = 0; i < num_players; ++i)
    {
      for (unsigned j = 0; j < num_bullets; ++j)
      {
        float delta_x = player_positions[i].x_ - bullet_positions[j].x_;
        float delta_y = player_positions[i].y_ - bullet_positions[j].y_;

        if (delta_x * delta_x + delta_y * delta_y <= collision_radius * collision_radius)
        {
          bullet_destructibles[j].destroyed_ = true;
        }
      }
    }
  }
}