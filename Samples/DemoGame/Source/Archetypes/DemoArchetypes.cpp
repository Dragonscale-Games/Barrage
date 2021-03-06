/* ======================================================================== */
/*!
 * \file            DemoArchetypes.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 

 */
/* ======================================================================== */

#include "stdafx.h"
#include "DemoArchetypes.hpp"

#include <Engine/Engine.hpp>
#include <Objects/Components/EngineComponents.hpp>

using namespace Barrage;

namespace Demo
{
  void CreatePlayerArchetypes()
  {
    PoolArchetype* pool_archetype = new PoolArchetype;

    pool_archetype->tags_.push_back("Player");

    CircleCollider* circle_collider = new CircleCollider;
    circle_collider->radius_ = 16.0f;
    pool_archetype->sharedComponents_["Circle Collider"] = circle_collider;

    Sprite* sprite = new Sprite;
    sprite->layer_ = 0;
    sprite->texture_ = "TestShip";
    pool_archetype->sharedComponents_["Sprite"] = sprite;

    BoundaryBox* boundary_box = new BoundaryBox;
    boundary_box->xMin_ = 32.0f;
    boundary_box->xMax_ = 1248.0f;
    boundary_box->yMin_ = 32.0f;
    boundary_box->yMax_ = 688.0f;
    pool_archetype->sharedComponents_["Boundary Box"] = boundary_box;

    pool_archetype->componentArrayNames_.push_back("Position Array");
    pool_archetype->componentArrayNames_.push_back("Rotation Array");
    pool_archetype->componentArrayNames_.push_back("Scale Array");
    pool_archetype->componentArrayNames_.push_back("Velocity Array");

    Engine::Instance->Objects().AddPoolArchetype("Player Pool Archetype", pool_archetype);

    ObjectArchetype* object_archetype = new ObjectArchetype;

    PositionArray* position_array = new PositionArray;
    position_array->Allocate(1);
    position_array->data_->x_ = 640.0f;
    position_array->data_->y_ = 120.0f;
    object_archetype->components_["Position Array"] = position_array;

    RotationArray* rotation_array = new RotationArray;
    rotation_array->Allocate(1);
    object_archetype->components_["Rotation Array"] = rotation_array;

    ScaleArray* scale_array = new ScaleArray;
    scale_array->Allocate(1);
    scale_array->data_->w_ = 64.0f;
    scale_array->data_->h_ = 64.0f;
    object_archetype->components_["Scale Array"] = scale_array;

    VelocityArray* velocity_array = new VelocityArray;
    velocity_array->Allocate(1);
    object_archetype->components_["Velocity Array"] = velocity_array;

    Engine::Instance->Objects().AddObjectArchetype("Player Object Archetype", object_archetype);
  }

  void CreateBulletArchetypes()
  {
    PoolArchetype* pool_archetype = new PoolArchetype;

    pool_archetype->tags_.push_back("Bullet");

    CircleCollider* circle_collider = new CircleCollider;
    circle_collider->radius_ = 16.0f;
    pool_archetype->sharedComponents_["Circle Collider"] = circle_collider;

    Sprite* sprite = new Sprite;
    sprite->layer_ = 1;
    sprite->texture_ = "TestBullet";
    pool_archetype->sharedComponents_["Sprite"] = sprite;

    BoundaryBox* boundary_box = new BoundaryBox;
    boundary_box->xMin_ = -16.0f;
    boundary_box->xMax_ = 1296.0f;
    boundary_box->yMin_ = -16.0f;
    boundary_box->yMax_ = 736.0f;
    pool_archetype->sharedComponents_["Boundary Box"] = boundary_box;

    pool_archetype->componentArrayNames_.push_back("Position Array");
    pool_archetype->componentArrayNames_.push_back("Rotation Array");
    pool_archetype->componentArrayNames_.push_back("Scale Array");
    pool_archetype->componentArrayNames_.push_back("Velocity Array");
    pool_archetype->componentArrayNames_.push_back("Destructible Array");

    Engine::Instance->Objects().AddPoolArchetype("Bullet Pool Archetype", pool_archetype);

    ObjectArchetype* object_archetype = new ObjectArchetype;

    PositionArray* position_array = new PositionArray;
    position_array->Allocate(1);
    position_array->data_->x_ = 640.0f;
    position_array->data_->y_ = 120.0f;
    object_archetype->components_["Position Array"] = position_array;

    RotationArray* rotation_array = new RotationArray;
    rotation_array->Allocate(1);
    object_archetype->components_["Rotation Array"] = rotation_array;

    ScaleArray* scale_array = new ScaleArray;
    scale_array->Allocate(1);
    scale_array->data_->w_ = 32.0f;
    scale_array->data_->h_ = 32.0f;
    object_archetype->components_["Scale Array"] = scale_array;

    VelocityArray* velocity_array = new VelocityArray;
    velocity_array->Allocate(1);
    object_archetype->components_["Velocity Array"] = velocity_array;

    DestructibleArray* destructible_array = new DestructibleArray;
    destructible_array->Allocate(1);
    object_archetype->components_["Destructible Array"] = destructible_array;

    Engine::Instance->Objects().AddObjectArchetype("Bullet Object Archetype", object_archetype);
  }

  void CreateSpawnerArchetypes()
  {
    PoolArchetype* pool_archetype = new PoolArchetype;

    pool_archetype->tags_.push_back("Spawner");

    SpawnType bullet_spawn_type;
    bullet_spawn_type.archetypeName_ = "Bullet Object Archetype";
    bullet_spawn_type.poolName_ = "Bullet Pool";
    bullet_spawn_type.spawnNum_ = 0;
    bullet_spawn_type.sourceIndices_.resize(10000);
    bullet_spawn_type.spawnFuncs_.push_back("Match Position");
    bullet_spawn_type.spawnFuncs_.push_back("Random Direction");

    Spawner* spawner = new Spawner;
    spawner->spawnTypes_.push_back(bullet_spawn_type);
    pool_archetype->sharedComponents_["Spawner"] = spawner;

    RNG* rng = new RNG;
    pool_archetype->sharedComponents_["RNG"] = rng;

    pool_archetype->componentArrayNames_.push_back("Position Array");

    Engine::Instance->Objects().AddPoolArchetype("Spawner Pool Archetype", pool_archetype);

    ObjectArchetype* object_archetype = new ObjectArchetype;

    PositionArray* position_array = new PositionArray;
    position_array->Allocate(1);
    position_array->data_->x_ = 640.0f;
    position_array->data_->y_ = 600.0f;
    object_archetype->components_["Position Array"] = position_array;

    Engine::Instance->Objects().AddObjectArchetype("Spawner Object Archetype", object_archetype);
  }
}