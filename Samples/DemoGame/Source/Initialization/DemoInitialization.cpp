/* ======================================================================== */
/*!
 * \file            DemoInitialization.cpp
 * \par             Demo Game
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Sets up scene and space for the demo game.
 */
 /* ======================================================================== */

#include "DemoInitialization.hpp"

#include <Engine/Engine.hpp>
#include <Objects/Components/EngineComponents.hpp>
#include <Objects/ObjectManager.hpp>
#include "../Components/DemoComponents.hpp"
#include "../SpawnTypes.hpp"

namespace Demo
{
  using namespace Barrage;
  
  Space* CreateDemoSpace()
  {
    Space* demo_space = new Space;
    ObjectManager& object_manager = demo_space->GetObjectManager();

    CreatePlayerArchetypes(object_manager);
    CreateBulletArchetypes(object_manager);
    CreateSpawnerArchetypes(object_manager);

    Scene* demo_scene = CreateDemoScene();

    Engine::Instance->Scenes().AddScene("Demo Scene", demo_scene);
    demo_space->SetScene("Demo Scene");

    return demo_space;
  }
  
  Scene* CreateDemoScene()
  {
    PoolInfo player_pool("Player Pool");
    player_pool.objects_.push_back("Player Object");

    PoolInfo spawner_pool("Spawner Pool");
    spawner_pool.objects_.push_back("Spawner Object");

    PoolInfo bullet_pool("Bullet Pool");

    Scene* demo_scene = new Scene;

    demo_scene->AddStartingPool(player_pool);
    demo_scene->AddStartingPool(spawner_pool);
    demo_scene->AddStartingPool(bullet_pool);

    return demo_scene;
  }

  void CreatePlayerArchetypes(Barrage::ObjectManager& objectManager)
  {
    PoolArchetype* pool_archetype = new PoolArchetype;

    SharedPlayer* player = new SharedPlayer;
    player->Data().speedFast_ = 7.0f;
    player->Data().speedSlow_ = 3.5f;
    pool_archetype->sharedComponents_["Player"] = player;

    SharedCircleCollider* circle_collider = new SharedCircleCollider;
    circle_collider->Data().radius_ = 16.0f;
    pool_archetype->sharedComponents_["CircleCollider"] = circle_collider;

    SharedSprite* sprite = new SharedSprite;
    sprite->Data().layer_ = 0;
    sprite->Data().texture_ = "TestShip";
    pool_archetype->sharedComponents_["Sprite"] = sprite;

    SharedBoundaryBox* boundary_box = new SharedBoundaryBox;
    boundary_box->Data().xMin_ = 32.0f;
    boundary_box->Data().xMax_ = 1920.0f - 32.0f;
    boundary_box->Data().yMin_ = 32.0f;
    boundary_box->Data().yMax_ = 1080.0f - 32.0f;
    pool_archetype->sharedComponents_["BoundaryBox"] = boundary_box;

    pool_archetype->componentArrayNames_.push_back("Position");
    pool_archetype->componentArrayNames_.push_back("Rotation");
    pool_archetype->componentArrayNames_.push_back("Scale");
    pool_archetype->componentArrayNames_.push_back("Velocity");
    pool_archetype->componentArrayNames_.push_back("TextureSpace");

    objectManager.AddPoolArchetype("Player Pool", pool_archetype);

    ObjectArchetype* object_archetype = new ObjectArchetype;

    PositionArray* position_array = new PositionArray;
    position_array->Allocate(1);
    position_array->data_->x_ = 960.0f;
    position_array->data_->y_ = 540.0f;
    object_archetype->components_["Position"] = position_array;

    RotationArray* rotation_array = new RotationArray;
    rotation_array->Allocate(1);
    object_archetype->components_["Rotation"] = rotation_array;

    ScaleArray* scale_array = new ScaleArray;
    scale_array->Allocate(1);
    scale_array->data_->w_ = 64.0f;
    scale_array->data_->h_ = 64.0f;
    object_archetype->components_["Scale"] = scale_array;

    VelocityArray* velocity_array = new VelocityArray;
    velocity_array->Allocate(1);
    object_archetype->components_["Velocity"] = velocity_array;

    TextureSpaceArray* tex_space_array = new TextureSpaceArray;
    tex_space_array->Allocate(1);
    tex_space_array->data_->uSize_ = 1.0f;
    tex_space_array->data_->vSize_ = 1.0f;
    tex_space_array->data_->u_ = 0.0f;
    tex_space_array->data_->v_ = 0.0f;
    object_archetype->components_["TextureSpace"] = tex_space_array;

    objectManager.AddObjectArchetype("Player Object", object_archetype);
  }

  void CreateBulletArchetypes(Barrage::ObjectManager& objectManager)
  {
    const unsigned MAX_BULLETS = 100000;
    
    PoolArchetype* pool_archetype = new PoolArchetype;

    pool_archetype->tags_.push_back("Bullet");

    SharedCircleCollider* circle_collider = new SharedCircleCollider;
    circle_collider->Data().radius_ = 16.0f;
    pool_archetype->sharedComponents_["CircleCollider"] = circle_collider;

    SharedSprite* sprite = new SharedSprite;
    sprite->Data().layer_ = 1;
    sprite->Data().texture_ = "TestBullet";
    pool_archetype->sharedComponents_["Sprite"] = sprite;

    SharedBoundaryBox* boundary_box = new SharedBoundaryBox;
    boundary_box->Data().xMin_ = -16.0f;
    boundary_box->Data().xMax_ = 1920.0f + 16.0f;
    boundary_box->Data().yMin_ = -16.0f;
    boundary_box->Data().yMax_ = 1080.0f + 16.0f;
    pool_archetype->sharedComponents_["BoundaryBox"] = boundary_box;

    pool_archetype->componentArrayNames_.push_back("Position");
    pool_archetype->componentArrayNames_.push_back("Rotation");
    pool_archetype->componentArrayNames_.push_back("Scale");
    pool_archetype->componentArrayNames_.push_back("Velocity");
    pool_archetype->componentArrayNames_.push_back("TextureSpace");
    pool_archetype->componentArrayNames_.push_back("Destructible");

    pool_archetype->capacity_ = MAX_BULLETS;

    objectManager.AddPoolArchetype("Bullet Pool", pool_archetype);

    ObjectArchetype* object_archetype = new ObjectArchetype;

    PositionArray* position_array = new PositionArray;
    position_array->Allocate(1);
    position_array->data_->x_ = 960.0f;
    position_array->data_->y_ = 880.0f;
    object_archetype->components_["Position"] = position_array;

    RotationArray* rotation_array = new RotationArray;
    rotation_array->Allocate(1);
    object_archetype->components_["Rotation"] = rotation_array;

    ScaleArray* scale_array = new ScaleArray;
    scale_array->Allocate(1);
    scale_array->data_->w_ = 32.0f;
    scale_array->data_->h_ = 32.0f;
    object_archetype->components_["Scale"] = scale_array;

    VelocityArray* velocity_array = new VelocityArray;
    velocity_array->Allocate(1);
    object_archetype->components_["Velocity"] = velocity_array;

    TextureSpaceArray* tex_space_array = new TextureSpaceArray;
    tex_space_array->Allocate(1);
    tex_space_array->data_->uSize_ = 1.0f;
    tex_space_array->data_->vSize_ = 1.0f;
    tex_space_array->data_->u_ = 0.0f;
    tex_space_array->data_->v_ = 0.0f;
    object_archetype->components_["TextureSpace"] = tex_space_array;

    DestructibleArray* destructible_array = new DestructibleArray;
    destructible_array->Allocate(1);
    object_archetype->components_["Destructible"] = destructible_array;

    objectManager.AddObjectArchetype("Bullet Object", object_archetype);
  }

  void CreateSpawnerArchetypes(Barrage::ObjectManager& objectManager)
  {
    PoolArchetype* pool_archetype = new PoolArchetype;

    pool_archetype->tags_.push_back("Spawner");

    SpawnType bullet_spawn_type;
    bullet_spawn_type.archetypeName_ = "Bullet Object";
    bullet_spawn_type.destinationPoolName_ = "Bullet Pool";
    bullet_spawn_type.spawnFuncs_.push_back("MatchPosition");
    bullet_spawn_type.spawnFuncs_.push_back("RandomDirection");

    SharedSpawner* spawner = new SharedSpawner;
    spawner->Data().spawnTypes_[BULLET_SPAWN_TYPE] = bullet_spawn_type;
    pool_archetype->sharedComponents_["Spawner"] = spawner;

    SharedRNG* rng = new SharedRNG;
    pool_archetype->sharedComponents_["RNG"] = rng;

    pool_archetype->componentArrayNames_.push_back("Position");

    objectManager.AddPoolArchetype("Spawner Pool", pool_archetype);

    ObjectArchetype* object_archetype = new ObjectArchetype;

    PositionArray* position_array = new PositionArray;
    position_array->Allocate(1);
    position_array->data_->x_ = 960.0f;
    position_array->data_->y_ = 880.0f;
    object_archetype->components_["Position"] = position_array;

    objectManager.AddObjectArchetype("Spawner Object", object_archetype);
  }
}