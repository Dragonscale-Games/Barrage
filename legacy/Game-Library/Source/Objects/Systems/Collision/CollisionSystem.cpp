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

#include "CollisionSystem.hpp"

#include "Objects/Components/GameComponents.hpp"

namespace Barrage
{
  CollisionSystem::CollisionSystem() :
    System()
  {
    systemComponents_.push_back("Tags");
    systemComponents_.push_back("Position");
    systemComponents_.push_back("CircleCollider");
  }

  void CollisionSystem::Subscribe(Pool* pool)
  {
    if (PoolMatchesSystem(pool))
    {
      Tags* pool_tags = static_cast<Tags*>(pool->poolComponents_["Tags"]);

      if (pool_tags->HasTag("Player"))
      {
        pools_.insert(std::pair<unsigned, Pool*>(0, pool));
      }

      if (pool_tags->HasTag("Bullet"))
      {
        pools_.insert(std::pair<unsigned, Pool*>(1, pool));
      }

      if (pool_tags->HasTag("Metaball"))
      {
        pools_.insert(std::pair<unsigned, Pool*>(2, pool));
      }
    }
  }

  void CollisionSystem::Update()
  {
    auto player_pools = pools_.equal_range(0);

    for (auto it = player_pools.first; it != player_pools.second; ++it)
    {
      auto bullet_pools = pools_.equal_range(1);

      for (auto jt = bullet_pools.first; jt != bullet_pools.second; ++jt)
      {
        UpdatePlayerBulletCollisions((*it).second, (*jt).second);
      }
    }

    auto metaball_pools = pools_.equal_range(2);

    for (auto it = metaball_pools.first; it != metaball_pools.second; ++it)
    {
      UpdateMetaballWallCollisions((*it).second);
    }
  }

  void CollisionSystem::UpdatePlayerBulletCollisions(Pool* player_pool, Pool* bullet_pool)
  {
    unsigned player_pool_size = player_pool->activeObjects_;
    unsigned bullet_pool_size = bullet_pool->activeObjects_;

    Position* player_positions = static_cast<Position*>(player_pool->objectComponents_.at("Position"));
    Position* bullet_positions = static_cast<Position*>(bullet_pool->objectComponents_.at("Position"));

    CircleCollider* player_colliders = static_cast<CircleCollider*>(player_pool->objectComponents_.at("CircleCollider"));
    CircleCollider* bullet_colliders = static_cast<CircleCollider*>(bullet_pool->objectComponents_.at("CircleCollider"));

    Destructible* bullet_destructibles = static_cast<Destructible*>(bullet_pool->objectComponents_.at("Destructible"));

    for (unsigned i = 0; i < player_pool_size; ++i)
    {
      for (unsigned j = 0; j < bullet_pool_size; ++j)
      {
        float delta_x = player_positions->data_[i].position_.x - bullet_positions->data_[j].position_.x;
        float delta_y = player_positions->data_[i].position_.y - bullet_positions->data_[j].position_.y;

        float collision_radius = player_colliders->data_[i].radius_ + bullet_colliders->data_[j].radius_;

        if (delta_x * delta_x + delta_y * delta_y <= collision_radius * collision_radius)
        {
          bullet_destructibles->data_[j].destroyed_ = true;
        }
        else if (bullet_positions->data_[j].position_.x > 1280.0f)
        {
          bullet_destructibles->data_[j].destroyed_ = true;
        }
        else if (bullet_positions->data_[j].position_.x < 0.0f)
        {
          bullet_destructibles->data_[j].destroyed_ = true;
        }
        else if (bullet_positions->data_[j].position_.y > 720.0f)
        {
          bullet_destructibles->data_[j].destroyed_ = true;
        }
        else if (bullet_positions->data_[j].position_.y < 0.0f)
        {
          bullet_destructibles->data_[j].destroyed_ = true;
        }
      }
    }
  }

  void CollisionSystem::UpdateMetaballWallCollisions(Pool* metaball_pool)
  {
    unsigned metaball_pool_size = metaball_pool->activeObjects_;

    Position* metaball_positions = static_cast<Position*>(metaball_pool->objectComponents_.at("Position"));
    Velocity* metaball_velocities = static_cast<Velocity*>(metaball_pool->objectComponents_.at("Velocity"));
    CircleCollider* metaball_colliders = static_cast<CircleCollider*>(metaball_pool->objectComponents_.at("CircleCollider"));

    for (unsigned i = 0; i < metaball_pool_size; ++i)
    {
      if (metaball_positions->data_[i].position_.x > 1280.0f - metaball_colliders->data_[i].radius_)
      {
        metaball_positions->data_[i].position_.x = (1280.0f - metaball_colliders->data_[i].radius_) - (metaball_positions->data_[i].position_.x - (1280.0f - metaball_colliders->data_[i].radius_));
        metaball_velocities->data_[i].velocity_.x = -metaball_velocities->data_[i].velocity_.x;
      }
      else if (metaball_positions->data_[i].position_.x < 0.0f + metaball_colliders->data_[i].radius_)
      {
        metaball_positions->data_[i].position_.x = metaball_colliders->data_[i].radius_ + (metaball_colliders->data_[i].radius_ - metaball_positions->data_[i].position_.x);
        metaball_velocities->data_[i].velocity_.x = -metaball_velocities->data_[i].velocity_.x;
      }

      if (metaball_positions->data_[i].position_.y > 720.0f - metaball_colliders->data_[i].radius_)
      {
        metaball_positions->data_[i].position_.y = (720.0f - metaball_colliders->data_[i].radius_) - (metaball_positions->data_[i].position_.y - (720.0f - metaball_colliders->data_[i].radius_));
        metaball_velocities->data_[i].velocity_.y = -metaball_velocities->data_[i].velocity_.y;
      }
      else if (metaball_positions->data_[i].position_.y < 0.0f + metaball_colliders->data_[i].radius_)
      {
        metaball_positions->data_[i].position_.y = metaball_colliders->data_[i].radius_ + (metaball_colliders->data_[i].radius_ - metaball_positions->data_[i].position_.y);
        metaball_velocities->data_[i].velocity_.y = -metaball_velocities->data_[i].velocity_.y;
      }
    }
  }
}