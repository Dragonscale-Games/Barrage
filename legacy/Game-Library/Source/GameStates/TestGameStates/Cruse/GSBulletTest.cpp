/* ======================================================================== */
/*!
 * \file            GSBulletTest.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <description>

 */
 /* ======================================================================== */

#include "GSBulletTest.hpp"
#include "GameStates/GSEntry.hpp"
#include "GameStates/TestGameStates/GSCruse.hpp"

#include <Engine/Engine.hpp>
#include <Random/Random.hpp>

#include <Objects/Components/EngineComponents.hpp>
#include <Objects/Components/GameComponents.hpp>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <math.h>

namespace Barrage
{
  glm::vec2* player_velocity_ref;
  unsigned* GSBulletTest::numBullets_ = nullptr;

  GSBulletTest::GSBulletTest() : GameState(Enter, Update, Exit)
  {
  }

  void GSBulletTest::Enter()
  {
    const unsigned MAX_BULLETS = 100000;

    PoolArchetype* spawner_archetype = new PoolArchetype;

    RNG* spawner_rng = new RNG;
    spawner_archetype->poolComponents_["RNG"] = spawner_rng;

    SpawnType spawn_type;
    spawn_type.archetypeName_ = "Bullet Object Archetype";
    spawn_type.initializerNames_.push_back("Random Direction");
    spawn_type.initializerNames_.push_back("Circle Spawn");
    spawn_type.poolName_ = "Bullet Pool";
    spawn_type.spawnNum_ = MAX_BULLETS / 100;

    Spawner* spawner_spawner = new Spawner;
    spawner_spawner->spawnTypes_.push_back(spawn_type);
    spawner_archetype->poolComponents_["Spawner"] = spawner_spawner;

    Timer* spawner_timer = new Timer;
    spawner_archetype->poolComponents_["Timer"] = spawner_timer;

    Engine::Objects().AddPoolArchetype("Spawner Archetype", spawner_archetype);
    Engine::Objects().CreatePool("Spawner", "Spawner Archetype");

    PoolArchetype* player_pool_archetype = new PoolArchetype;

    Tags* player_tags = new Tags;
    player_tags->tagSet_.insert("Player");
    player_pool_archetype->poolComponents_["Tags"] = player_tags;

    Sprite* player_sprite = new Sprite;
    player_sprite->layer_ = 0;
    player_sprite->texture_ = std::string("TestShip");
    player_pool_archetype->poolComponents_["Sprite"] = player_sprite;

    player_pool_archetype->objectComponents_.push_back("Position");
    player_pool_archetype->objectComponents_.push_back("Scale");
    player_pool_archetype->objectComponents_.push_back("Rotation");
    player_pool_archetype->objectComponents_.push_back("Velocity");
    player_pool_archetype->objectComponents_.push_back("CircleCollider");

    Engine::Objects().AddPoolArchetype("Player Pool Archetype", player_pool_archetype);
    Engine::Objects().CreatePool("Player Pool", "Player Pool Archetype");

    PoolArchetype* bullet_pool_archetype = new PoolArchetype;

    Tags* bullet_tags = new Tags;
    bullet_tags->tagSet_.insert("Bullet");
    bullet_pool_archetype->poolComponents_["Tags"] = bullet_tags;

    Sprite* bullet_sprite = new Sprite;
    bullet_sprite->layer_ = 1;
    bullet_sprite->texture_ = std::string("Test32");
    bullet_pool_archetype->poolComponents_["Sprite"] = bullet_sprite;

    bullet_pool_archetype->objectComponents_.push_back("Position");
    bullet_pool_archetype->objectComponents_.push_back("Scale");
    bullet_pool_archetype->objectComponents_.push_back("Rotation");
    bullet_pool_archetype->objectComponents_.push_back("Velocity");
    bullet_pool_archetype->objectComponents_.push_back("CircleCollider");
    bullet_pool_archetype->objectComponents_.push_back("Destructible");

    Engine::Objects().AddPoolArchetype("Bullet Pool Archetype", bullet_pool_archetype);
    Engine::Objects().CreatePool("Bullet Pool", "Bullet Pool Archetype", MAX_BULLETS);

    ObjectArchetype* player_object_archetype = new ObjectArchetype;
    ObjectComponentMap& player_component_map = player_object_archetype->objectComponents_;

    Position* player_position = new Position;             player_position->Allocate(1);
    Scale* player_scale = new Scale;                      player_scale->Allocate(1);
    Rotation* player_rotation = new Rotation;             player_rotation->Allocate(1);
    Velocity* player_velocity = new Velocity;             player_velocity->Allocate(1);
    CircleCollider* player_collider = new CircleCollider; player_collider->Allocate(1);

    player_position->data_->position_.x = 640.0f;
    player_position->data_->position_.y = 120.0f;

    player_scale->data_->dimensions_.x = 64.0f;
    player_scale->data_->dimensions_.y = 64.0f;

    player_rotation->data_->angle_ = 0.0f;

    player_velocity->data_->velocity_.x = 0.0f;
    player_velocity->data_->velocity_.y = 0.0f;

    player_collider->data_->radius_ = 16.0f;

    player_component_map["Position"] = player_position;
    player_component_map["Scale"] = player_scale;
    player_component_map["Rotation"] = player_rotation;
    player_component_map["Velocity"] = player_velocity;
    player_component_map["CircleCollider"] = player_collider;

    Engine::Objects().AddObjectArchetype("Player Object Archetype", player_object_archetype);
    Engine::Objects().CreateObject("Player Pool", "Player Object Archetype");

    ObjectArchetype* bullet_object_archetype = new ObjectArchetype;
    ObjectComponentMap& bullet_component_map = bullet_object_archetype->objectComponents_;

    Position* bullet_position = new Position;             bullet_position->Allocate(1);
    Scale* bullet_scale = new Scale;                      bullet_scale->Allocate(1);
    Rotation* bullet_rotation = new Rotation;             bullet_rotation->Allocate(1);
    Velocity* bullet_velocity = new Velocity;             bullet_velocity->Allocate(1);
    CircleCollider* bullet_collider = new CircleCollider; bullet_collider->Allocate(1);
    Destructible* bullet_destructible = new Destructible; bullet_destructible->Allocate(1);

    bullet_position->data_->position_.x = 640.0f;
    bullet_position->data_->position_.y = 600.0f;

    bullet_scale->data_->dimensions_.x = 2.0f;
    bullet_scale->data_->dimensions_.y = 2.0f;

    bullet_rotation->data_->angle_ = 0.0f;

    bullet_velocity->data_->velocity_.x = 0.0f;
    bullet_velocity->data_->velocity_.y = 0.0f;

    bullet_collider->data_->radius_ = 16.0f;

    bullet_destructible->data_->destroyed_ = false;

    bullet_component_map["Position"] = bullet_position;
    bullet_component_map["Scale"] = bullet_scale;
    bullet_component_map["Rotation"] = bullet_rotation;
    bullet_component_map["Velocity"] = bullet_velocity;
    bullet_component_map["CircleCollider"] = bullet_collider;
    bullet_component_map["Destructible"] = bullet_destructible;

    Engine::Objects().AddObjectArchetype("Bullet Object Archetype", bullet_object_archetype);

    Pool* player_pool = Engine::Objects().GetPool("Player Pool");

    Velocity* player_velocity_component = dynamic_cast<Velocity*>(player_pool->objectComponents_["Velocity"]);
    player_velocity_ref = &(player_velocity_component->data_->velocity_);

    numBullets_ = &(Engine::Objects().GetPool("Bullet Pool")->activeObjects_);
  }

  void GSBulletTest::Update()
  {
    float speed = 10.0f;

    // manually updating input for now
    if (Engine::Input().KeyIsDown(KEY_LEFT))
    {
      player_velocity_ref->x = -speed;
    }
    else if (Engine::Input().KeyIsDown(KEY_RIGHT))
    {
      player_velocity_ref->x = speed;
    }
    else
    {
      player_velocity_ref->x = 0.0f;
    }

    if (Engine::Input().KeyIsDown(KEY_UP))
    {
      player_velocity_ref->y = speed;
    }
    else if (Engine::Input().KeyIsDown(KEY_DOWN))
    {
      player_velocity_ref->y = -speed;
    }
    else
    {
      player_velocity_ref->y = 0.0f;
    }
  }

  void GSBulletTest::Exit()
  {
    numBullets_ = nullptr;
    
    Engine::Objects().DeletePool("Player Pool");
    Engine::Objects().DeletePool("Spawner");
    Engine::Objects().DeletePool("Bullet Pool");
  }

  unsigned GSBulletTest::GetNumBullets()
  {
    if (numBullets_)
    {
      return *numBullets_;
    }
    else
    {
      return 0;
    }
  }
}