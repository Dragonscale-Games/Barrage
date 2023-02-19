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
#include "Source/Components/DemoComponents.hpp"

namespace Demo
{
  using namespace Barrage;
  
  static const unsigned CIRCLE_BULLET_POOLS = 0;
  static const unsigned CIRCLE_PLAYER_POOLS = 1;
  static const unsigned BOUNDED_BULLET_POOLS = 2;
  
  CollisionSystem::CollisionSystem() :
    System()
  {
    PoolType circle_bullet_type;
    circle_bullet_type.AddSharedComponent("CircleCollider");
    circle_bullet_type.AddComponentArray("Position");
    circle_bullet_type.AddComponentArray("Destructible");
    circle_bullet_type.AddTag("Bullet");
    poolTypes_[CIRCLE_BULLET_POOLS] = circle_bullet_type;

    PoolType bounded_bullet_type;
    bounded_bullet_type.AddComponentArray("Position");
    bounded_bullet_type.AddSharedComponent("BoundaryBox");
    bounded_bullet_type.AddComponentArray("Destructible");
    bounded_bullet_type.AddTag("Bullet");
    poolTypes_[BOUNDED_BULLET_POOLS] = bounded_bullet_type;

    PoolType circle_player_type;
    circle_player_type.AddSharedComponent("CircleCollider");
    circle_player_type.AddComponentArray("Position");
    circle_player_type.AddSharedComponent("Player");
    poolTypes_[CIRCLE_PLAYER_POOLS] = circle_player_type;
  }

  void CollisionSystem::Update()
  {
    UpdatePoolGroup(BOUNDED_BULLET_POOLS, UpdateBoundedBullets);
    
    UpdateInteraction(CIRCLE_PLAYER_POOLS, CIRCLE_BULLET_POOLS, UpdatePlayerBulletCollisions);
  }

  void CollisionSystem::UpdateBoundedBullets(Pool* pool)
  {
    PositionArray& position_array = *pool->GetComponentArray<Position>("Position");
    DestructibleArray& destructible_array = *pool->GetComponentArray<Destructible>("Destructible");

    BoundaryBox& boundary_box = pool->GetSharedComponent<BoundaryBox>("BoundaryBox")->Data();

    unsigned num_bullets = pool->numActiveObjects_;

    for (unsigned i = 0; i < num_bullets; ++i)
    {
      Position& pos = position_array.Data(i);

      if (pos.x_ < boundary_box.xMin_ || pos.x_ > boundary_box.xMax_ || pos.y_ < boundary_box.yMin_ || pos.y_ > boundary_box.yMax_)
      {
        destructible_array.Data(i).destroyed_ = true;
      }
    }
  }

  void CollisionSystem::UpdatePlayerBulletCollisions(Pool* player_pool, Pool* bullet_pool)
  {
    CircleCollider& player_collider = player_pool->GetSharedComponent<CircleCollider>("CircleCollider")->Data();
    CircleCollider& bullet_collider = bullet_pool->GetSharedComponent<CircleCollider>("CircleCollider")->Data();

    PositionArray& player_positions = *player_pool->GetComponentArray<Position>("Position");
    PositionArray& bullet_positions = *bullet_pool->GetComponentArray<Position>("Position");

    DestructibleArray& bullet_destructibles = *bullet_pool->GetComponentArray<Destructible>("Destructible");

    float collision_radius = player_collider.radius_ + bullet_collider.radius_;

    unsigned num_players = player_pool->numActiveObjects_;
    unsigned num_bullets = bullet_pool->numActiveObjects_;

    for (unsigned i = 0; i < num_players; ++i)
    {
      for (unsigned j = 0; j < num_bullets; ++j)
      {
        float delta_x = player_positions.Data(i).x_ - bullet_positions.Data(j).x_;
        float delta_y = player_positions.Data(i).y_ - bullet_positions.Data(j).y_;

        if (delta_x * delta_x + delta_y * delta_y <= collision_radius * collision_radius)
        {
          bullet_destructibles.Data(j).destroyed_ = true;
        }
      }
    }
  }
}