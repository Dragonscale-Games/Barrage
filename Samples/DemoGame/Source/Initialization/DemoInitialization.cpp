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
#include <Objects/Spawning/SpawnInfo.hpp>

namespace Demo
{
  using namespace Barrage;
  
  Space* CreateDemoSpace()
  {
    Space* demo_space = new Space;
    Scene* demo_scene = CreateDemoScene();

    Engine::Instance->Scenes().AddScene(demo_scene);
    demo_space->SetScene("Demo Scene");

    return demo_space;
  }
  
  Scene* CreateDemoScene()
  {
    Scene* demo_scene = new Scene("Demo Scene");

    CreatePlayerArchetypes(*demo_scene);
    CreateBulletArchetypes(*demo_scene);
    CreateSpawnerArchetypes(*demo_scene);

    return demo_scene;
  }

  void CreatePlayerArchetypes(Barrage::Scene& scene)
  {
    PoolArchetype* pool_archetype = new PoolArchetype("Player Pool");

    SharedPlayer* player = new SharedPlayer;
    player->Data().speedFast_ = 7.0f;
    player->Data().speedSlow_ = 3.5f;
    pool_archetype->AddSharedComponent("Player", player);

    SharedCircleCollider* circle_collider = new SharedCircleCollider;
    circle_collider->Data().radius_ = 16.0f;
    pool_archetype->AddSharedComponent("CircleCollider", circle_collider);

    SharedSprite* sprite = new SharedSprite;
    sprite->Data().layer_ = 0;
    sprite->Data().texture_ = "TestShip";
    pool_archetype->AddSharedComponent("Sprite", sprite);

    SharedBoundaryBox* boundary_box = new SharedBoundaryBox;
    boundary_box->Data().xMin_ = 32.0f;
    boundary_box->Data().xMax_ = 1920.0f - 32.0f;
    boundary_box->Data().yMin_ = 32.0f;
    boundary_box->Data().yMax_ = 1080.0f - 32.0f;
    pool_archetype->AddSharedComponent("BoundaryBox", boundary_box);

    pool_archetype->AddComponentArrayName("Position");
    pool_archetype->AddComponentArrayName("Rotation");
    pool_archetype->AddComponentArrayName("Scale");
    pool_archetype->AddComponentArrayName("Velocity");
    pool_archetype->AddComponentArrayName("TextureSpace");

    ObjectArchetype* object_archetype = new ObjectArchetype("Player Object");

    PositionArray* position_array = new PositionArray;
    position_array->data_->x_ = 960.0f;
    position_array->data_->y_ = 540.0f;
    object_archetype->AddComponentArray("Position", position_array);

    RotationArray* rotation_array = new RotationArray;
    object_archetype->AddComponentArray("Rotation", rotation_array);

    ScaleArray* scale_array = new ScaleArray;
    scale_array->data_->w_ = 64.0f;
    scale_array->data_->h_ = 64.0f;
    object_archetype->AddComponentArray("Scale", scale_array);

    VelocityArray* velocity_array = new VelocityArray;
    object_archetype->AddComponentArray("Velocity", velocity_array);

    TextureSpaceArray* tex_space_array = new TextureSpaceArray;
    tex_space_array->data_->uSize_ = 1.0f;
    tex_space_array->data_->vSize_ = 1.0f;
    tex_space_array->data_->u_ = 0.0f;
    tex_space_array->data_->v_ = 0.0f;
    object_archetype->AddComponentArray("TextureSpace", tex_space_array);

    pool_archetype->AddStartingObject(object_archetype);

    scene.AddPoolArchetype(pool_archetype);
  }

  void CreateBulletArchetypes(Barrage::Scene& scene)
  {
    const unsigned MAX_BULLETS = 100000;
    
    PoolArchetype* pool_archetype = new PoolArchetype("Bullet Pool", MAX_BULLETS);

    pool_archetype->AddTag("Bullet");
    pool_archetype->AddTag("Bullet Pool");

    SharedCircleCollider* circle_collider = new SharedCircleCollider;
    circle_collider->Data().radius_ = 16.0f;
    pool_archetype->AddSharedComponent("CircleCollider", circle_collider);

    SharedSprite* sprite = new SharedSprite;
    sprite->Data().layer_ = 1;
    sprite->Data().texture_ = "TestBullet";
    pool_archetype->AddSharedComponent("Sprite", sprite);

    SharedBoundaryBox* boundary_box = new SharedBoundaryBox;
    boundary_box->Data().xMin_ = -16.0f;
    boundary_box->Data().xMax_ = 1920.0f + 16.0f;
    boundary_box->Data().yMin_ = -16.0f;
    boundary_box->Data().yMax_ = 1080.0f + 16.0f;
    pool_archetype->AddSharedComponent("BoundaryBox", boundary_box);

    pool_archetype->AddComponentArrayName("Position");
    pool_archetype->AddComponentArrayName("Rotation");
    pool_archetype->AddComponentArrayName("Scale");
    pool_archetype->AddComponentArrayName("Velocity");
    pool_archetype->AddComponentArrayName("TextureSpace");
    pool_archetype->AddComponentArrayName("Destructible");

    ObjectArchetype* object_archetype = new ObjectArchetype("Bullet Object");

    PositionArray* position_array = new PositionArray;
    position_array->data_->x_ = 960.0f;
    position_array->data_->y_ = 880.0f;
    object_archetype->AddComponentArray("Position", position_array);

    RotationArray* rotation_array = new RotationArray;
    object_archetype->AddComponentArray("Rotation", rotation_array);

    ScaleArray* scale_array = new ScaleArray;
    scale_array->data_->w_ = 32.0f;
    scale_array->data_->h_ = 32.0f;
    object_archetype->AddComponentArray("Scale", scale_array);

    VelocityArray* velocity_array = new VelocityArray;
    object_archetype->AddComponentArray("Velocity", velocity_array);

    TextureSpaceArray* tex_space_array = new TextureSpaceArray;
    tex_space_array->data_->uSize_ = 1.0f;
    tex_space_array->data_->vSize_ = 1.0f;
    tex_space_array->data_->u_ = 0.0f;
    tex_space_array->data_->v_ = 0.0f;
    object_archetype->AddComponentArray("TextureSpace", tex_space_array);

    DestructibleArray* destructible_array = new DestructibleArray;
    object_archetype->AddComponentArray("Destructible", destructible_array);

    pool_archetype->AddSpawnArchetype(object_archetype);

    scene.AddPoolArchetype(pool_archetype);
  }

  void CreateSpawnerArchetypes(Barrage::Scene& scene)
  {    
    PoolArchetype* pool_archetype = new PoolArchetype("Spawner Pool");

    pool_archetype->AddTag("Spawner");

    SpawnInfo bullet_spawn_type;
    bullet_spawn_type.archetypeName_ = "Bullet Object";
    bullet_spawn_type.spawnFunctions_.push_back("MatchPosition");
    bullet_spawn_type.spawnFunctions_.push_back("RandomDirection");

    SharedSpawner* spawner = new SharedSpawner;
    spawner->Data().spawnTypes_[BULLET_SPAWN_TYPE] = bullet_spawn_type;
    pool_archetype->AddSharedComponent("Spawner", spawner);

    SharedRNG* rng = new SharedRNG;
    pool_archetype->AddSharedComponent("RNG", rng);

    pool_archetype->AddComponentArrayName("Position");

    ObjectArchetype* object_archetype = new ObjectArchetype("Spawner Object");

    PositionArray* position_array = new PositionArray;
    position_array->data_->x_ = 960.0f;
    position_array->data_->y_ = 880.0f;
    object_archetype->AddComponentArray("Position", position_array);

    pool_archetype->AddStartingObject(object_archetype);

    scene.AddPoolArchetype(pool_archetype);
  }
}