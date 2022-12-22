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

    demo_space->AddScene("Demo Scene", demo_scene);
    demo_space->SetScene("Demo Scene");

    return demo_space;
  }
  
  Scene* CreateDemoScene()
  {
    const unsigned MAX_BULLETS = 100000;

    PoolInfo player_pool("Player Pool", "Player Pool Archetype");
    player_pool.objects_.push_back("Player Object Archetype");

    PoolInfo spawner_pool("Spawner Pool", "Spawner Pool Archetype");
    spawner_pool.objects_.push_back("Spawner Object Archetype");

    PoolInfo bullet_pool("Bullet Pool", "Bullet Pool Archetype", MAX_BULLETS);

    Scene* demo_scene = new Scene;

    demo_scene->AddStartingPool(player_pool);
    demo_scene->AddStartingPool(spawner_pool);
    demo_scene->AddStartingPool(bullet_pool);

    return demo_scene;
  }

  void CreatePlayerArchetypes(Barrage::ObjectManager& objectManager)
  {
    PoolArchetype* pool_archetype = new PoolArchetype;

    Player* player = new Player;
    player->speedFast_ = 7.0f;
    player->speedSlow_ = 3.5f;
    pool_archetype->sharedComponents_["Player"] = player;

    CircleCollider* circle_collider = new CircleCollider;
    circle_collider->radius_ = 16.0f;
    pool_archetype->sharedComponents_["CircleCollider"] = circle_collider;

    Sprite* sprite = new Sprite;
    sprite->layer_ = 0;
    sprite->texture_ = "TestShip";
    pool_archetype->sharedComponents_["Sprite"] = sprite;

    BoundaryBox* boundary_box = new BoundaryBox;
    boundary_box->xMin_ = 32.0f;
    boundary_box->xMax_ = 1920.0f - 32.0f;
    boundary_box->yMin_ = 32.0f;
    boundary_box->yMax_ = 1080.0f - 32.0f;
    pool_archetype->sharedComponents_["BoundaryBox"] = boundary_box;

    pool_archetype->componentArrayNames_.push_back("PositionArray");
    pool_archetype->componentArrayNames_.push_back("RotationArray");
    pool_archetype->componentArrayNames_.push_back("ScaleArray");
    pool_archetype->componentArrayNames_.push_back("VelocityArray");
    pool_archetype->componentArrayNames_.push_back("TextureSpaceArray");

    objectManager.AddPoolArchetype("Player Pool Archetype", pool_archetype);

    ObjectArchetype* object_archetype = new ObjectArchetype;

    PositionArray* position_array = new PositionArray;
    position_array->Allocate(1);
    position_array->data_->x_ = 960.0f;
    position_array->data_->y_ = 200.0f;
    object_archetype->components_["PositionArray"] = position_array;

    RotationArray* rotation_array = new RotationArray;
    rotation_array->Allocate(1);
    object_archetype->components_["RotationArray"] = rotation_array;

    ScaleArray* scale_array = new ScaleArray;
    scale_array->Allocate(1);
    scale_array->data_->w_ = 64.0f;
    scale_array->data_->h_ = 64.0f;
    object_archetype->components_["ScaleArray"] = scale_array;

    VelocityArray* velocity_array = new VelocityArray;
    velocity_array->Allocate(1);
    object_archetype->components_["VelocityArray"] = velocity_array;

    TextureSpaceArray* tex_space_array = new TextureSpaceArray;
    tex_space_array->Allocate(1);
    object_archetype->components_["TextureSpaceArray"] = tex_space_array;

    objectManager.AddObjectArchetype("Player Object Archetype", object_archetype);
  }

  void CreateBulletArchetypes(Barrage::ObjectManager& objectManager)
  {
    PoolArchetype* pool_archetype = new PoolArchetype;

    pool_archetype->tags_.push_back("Bullet");

    CircleCollider* circle_collider = new CircleCollider;
    circle_collider->radius_ = 16.0f;
    pool_archetype->sharedComponents_["CircleCollider"] = circle_collider;

    Sprite* sprite = new Sprite;
    sprite->layer_ = 1;
    sprite->texture_ = "TestBullet";
    pool_archetype->sharedComponents_["Sprite"] = sprite;

    BoundaryBox* boundary_box = new BoundaryBox;
    boundary_box->xMin_ = -16.0f;
    boundary_box->xMax_ = 1920.0f + 16.0f;
    boundary_box->yMin_ = -16.0f;
    boundary_box->yMax_ = 1080.0f + 16.0f;
    pool_archetype->sharedComponents_["BoundaryBox"] = boundary_box;

    pool_archetype->componentArrayNames_.push_back("PositionArray");
    pool_archetype->componentArrayNames_.push_back("RotationArray");
    pool_archetype->componentArrayNames_.push_back("ScaleArray");
    pool_archetype->componentArrayNames_.push_back("VelocityArray");
    pool_archetype->componentArrayNames_.push_back("TextureSpaceArray");
    pool_archetype->componentArrayNames_.push_back("DestructibleArray");

    objectManager.AddPoolArchetype("Bullet Pool Archetype", pool_archetype);

    ObjectArchetype* object_archetype = new ObjectArchetype;

    PositionArray* position_array = new PositionArray;
    position_array->Allocate(1);
    position_array->data_->x_ = 640.0f;
    position_array->data_->y_ = 120.0f;
    object_archetype->components_["PositionArray"] = position_array;

    RotationArray* rotation_array = new RotationArray;
    rotation_array->Allocate(1);
    object_archetype->components_["RotationArray"] = rotation_array;

    ScaleArray* scale_array = new ScaleArray;
    scale_array->Allocate(1);
    scale_array->data_->w_ = 32.0f;
    scale_array->data_->h_ = 32.0f;
    object_archetype->components_["ScaleArray"] = scale_array;

    VelocityArray* velocity_array = new VelocityArray;
    velocity_array->Allocate(1);
    object_archetype->components_["VelocityArray"] = velocity_array;

    TextureSpaceArray* tex_space_array = new TextureSpaceArray;
    tex_space_array->Allocate(1);
    tex_space_array->data_->u_ = 0.5f;
    tex_space_array->data_->v_ = 0.5f;
    tex_space_array->data_->uSize_ = 0.5f;
    tex_space_array->data_->vSize_ = 0.5f;
    object_archetype->components_["TextureSpaceArray"] = tex_space_array;

    DestructibleArray* destructible_array = new DestructibleArray;
    destructible_array->Allocate(1);
    object_archetype->components_["DestructibleArray"] = destructible_array;

    objectManager.AddObjectArchetype("Bullet Object Archetype", object_archetype);
  }

  void CreateSpawnerArchetypes(Barrage::ObjectManager& objectManager)
  {
    PoolArchetype* pool_archetype = new PoolArchetype;

    pool_archetype->tags_.push_back("Spawner");

    SpawnType bullet_spawn_type;
    bullet_spawn_type.archetypeName_ = "Bullet Object Archetype";
    bullet_spawn_type.destinationPoolName_ = "Bullet Pool";
    bullet_spawn_type.spawnFuncs_.push_back("MatchPosition");
    bullet_spawn_type.spawnFuncs_.push_back("RandomDirection");

    Spawner* spawner = new Spawner;
    spawner->spawnTypes_[BULLET_SPAWN_TYPE] = bullet_spawn_type;
    pool_archetype->sharedComponents_["Spawner"] = spawner;

    RNG* rng = new RNG;
    pool_archetype->sharedComponents_["RNG"] = rng;

    pool_archetype->componentArrayNames_.push_back("PositionArray");

    objectManager.AddPoolArchetype("Spawner Pool Archetype", pool_archetype);

    ObjectArchetype* object_archetype = new ObjectArchetype;

    PositionArray* position_array = new PositionArray;
    position_array->Allocate(1);
    position_array->data_->x_ = 960.0f;
    position_array->data_->y_ = 880.0f;
    object_archetype->components_["PositionArray"] = position_array;

    objectManager.AddObjectArchetype("Spawner Object Archetype", object_archetype);
  }
}