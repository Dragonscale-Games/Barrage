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

#include "ComponentArrays/PositionArray.hpp"
#include "ComponentArrays/DestructibleArray.hpp"

#include "Components/BoundaryBox.hpp"
#include "Components/CircleCollider.hpp"
#include "Components/Player.hpp"

#include "Spaces/Space.hpp"

namespace Barrage
{
  CollisionSystem::CollisionSystem() :
    System()
  {
    PoolType circle_bullet_type;
    circle_bullet_type.AddComponent("CircleCollider");
    circle_bullet_type.AddComponentArray("Position");
    circle_bullet_type.AddComponentArray("Destructible");
    circle_bullet_type.AddTag("Bullet");
    poolTypes_["Circle Bullet Pools"] = circle_bullet_type;

    PoolType bounded_bullet_type;
    bounded_bullet_type.AddComponentArray("Position");
    bounded_bullet_type.AddComponent("BoundaryBox");
    bounded_bullet_type.AddComponentArray("Destructible");
    bounded_bullet_type.AddTag("Bullet");
    poolTypes_["Bounded Bullet Pools"] = bounded_bullet_type;

    PoolType circle_player_type;
    circle_player_type.AddComponent("CircleCollider");
    circle_player_type.AddComponentArray("Position");
    circle_player_type.AddComponent("Player");
    poolTypes_["Circle Player Pools"] = circle_player_type;
  }

  void CollisionSystem::Update()
  {
    UpdatePoolGroup("Bounded Bullet Pools", UpdateBoundedBullets);

    UpdateInteraction("Circle Player Pools", "Circle Bullet Pools", UpdatePlayerBulletCollisions);
    UpdateInteraction("Circle Player Pools", "Circle Bullet Pools", ClearBulletsOnPlayerHit);
    UpdatePoolGroup("Circle Player Pools", ResetPlayerHit);
  }

  void CollisionSystem::UpdateBoundedBullets(Pool* pool)
  {
    PositionArray& position_array = *pool->GetComponentArray<Position>("Position");
    DestructibleArray& destructible_array = *pool->GetComponentArray<Destructible>("Destructible");

    BoundaryBox& boundary_box = pool->GetComponent<BoundaryBox>("BoundaryBox")->Data();

    unsigned num_bullets = pool->GetActiveObjectCount();

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
    Player& player = player_pool->GetComponent<Player>("Player")->Data();
    
    CircleCollider& player_collider = player_pool->GetComponent<CircleCollider>("CircleCollider")->Data();
    CircleCollider& bullet_collider = bullet_pool->GetComponent<CircleCollider>("CircleCollider")->Data();

    PositionArray& player_positions = *player_pool->GetComponentArray<Position>("Position");
    PositionArray& bullet_positions = *bullet_pool->GetComponentArray<Position>("Position");

    DestructibleArray& bullet_destructibles = *bullet_pool->GetComponentArray<Destructible>("Destructible");

    float collision_radius = player_collider.radius_ + bullet_collider.radius_;

    unsigned num_players = player_pool->GetActiveObjectCount();
    unsigned num_bullets = bullet_pool->GetActiveObjectCount();

    for (unsigned i = 0; i < num_players; ++i)
    {
      for (unsigned j = 0; j < num_bullets; ++j)
      {
        float delta_x = player_positions.Data(i).x_ - bullet_positions.Data(j).x_;
        float delta_y = player_positions.Data(i).y_ - bullet_positions.Data(j).y_;

        if (delta_x * delta_x + delta_y * delta_y <= collision_radius * collision_radius)
        {
          player.playerHit_ = true;
          bullet_destructibles.Data(j).destroyed_ = true;
        }
      }
    }
  }

  void CollisionSystem::ClearBulletsOnPlayerHit(Pool* player_pool, Pool* bullet_pool)
  {
    Player& player = player_pool->GetComponent<Player>("Player")->Data();

    if (player.playerHit_ && !player.isInvincible_)
    {
      DestructibleArray& bullet_destructibles = *bullet_pool->GetComponentArray<Destructible>("Destructible");

      unsigned num_bullets = bullet_pool->GetActiveObjectCount();

      for (unsigned i = 0; i < num_bullets; ++i)
      {
        bullet_destructibles.Data(i).destroyed_ = true;
      }
    }
  }

  void CollisionSystem::ResetPlayerHit(Pool* pool)
  {
    Player& player = pool->GetComponent<Player>("Player")->Data();

    player.playerHit_ = false;
  }
}