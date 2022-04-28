///* ======================================================================== */
///*!
// * \file            GSMetaballs.cpp
// * \par             Barrage Engine
// * \author          David Cruse
// * \par             david.n.cruse\@gmail.com
//
// * \brief
//   <description>
//
// */
///* ======================================================================== */
//
//#include "GSMetaballs.hpp"
//#include "GameStates/GSEntry.hpp"
//#include "GameStates/TestGameStates/GSCruse.hpp"
//
//#include <Engine/Engine.hpp>
//#include <Random/Random.hpp>
//#include <TempRenderer/TestRenderer.hpp>
//
//#include <Objects/ObjectManager.hpp>
//
//#include <Objects/Systems/Creation/CreationSystem.hpp>
//#include <Objects/Systems/Destruction/DestructionSystem.hpp>
//#include <Objects/Systems/Graphics/DrawSystem.hpp>
//#include <Objects/Systems/Collision/CollisionSystem.hpp>
//#include <Objects/Systems/Movement/MovementSystem.hpp>
//
//#include <GLAD/gl.h>
//#include <GLFW/glfw3.h>
//#include <GLM/gtc/matrix_transform.hpp>
//
//#include <iostream>
//#include <math.h>
//
//namespace Barrage
//{
//  
//
//  Pool* metaball_pool;
//
//  CreationSystem* creation_system;
//  CollisionSystem* collision_system;
//  MovementSystem* movement_system;
//  DrawSystem* draw_system;
//
//  ObjectComponentMap* metaball_component_map;
//  ObjectArchetype* metaball_archetype;
//
//  Position* metaball_position;
//  Scale* metaball_scale;
//  Rotation* metaball_rotation;
//  Velocity* metaball_velocity;
//  CircleCollider* metaball_collider;
//
//  Random* rng;
//
//  const unsigned num_metaballs = 20;
//
//  const unsigned num_cells_x = 480;
//  const unsigned num_cells_y = 270;
//
//  const unsigned num_grid_points_x = num_cells_x + 1;
//  const unsigned num_grid_points_y = num_cells_y + 1;
//
//  float grid_values[num_grid_points_x][num_grid_points_y];
//  unsigned cell_values[num_cells_x][num_cells_y];
//
//  std::vector<glm::vec2> vertices;
//  std::vector<glm::vec2> scales;
//  std::vector<float> rotations;
//
//  bool draw_sprites;
//
//	// up, right, down, left
//	char vertex_locations[16][4] =
//	{
//		{ 0, 0, 0, 0 }, //  0
//		{ 0, 0, 1, 1 }, //  1
//		{ 0, 1, 1, 0 }, //  2
//		{ 0, 1, 0, 1 }, //  3
//		{ 1, 1, 0, 0 }, //  4
//		{ 1, 1, 1, 1 }, //  5
//		{ 1, 0, 1, 0 }, //  6
//		{ 1, 0, 0, 1 }, //  7
//		{ 1, 0, 0, 1 }, //  8
//		{ 1, 0, 1, 0 }, //  9
//		{ 1, 1, 1, 1 }, // 10
//		{ 1, 1, 0, 0 }, // 11
//		{ 0, 1, 0, 1 }, // 12
//		{ 0, 1, 1, 0 }, // 13
//		{ 0, 0, 1, 1 }, // 14
//		{ 0, 0, 0, 0 }  // 15
//	};
//
//  GSMetaballs::GSMetaballs() : GameState(Enter, Update, Exit)
//  {
//  }
//
//  void GSMetaballs::Enter()
//  { 
//    pool_factory = new PoolFactory;
//
//    pool_factory->RegisterComponent<Position>("Position");
//    pool_factory->RegisterComponent<Scale>("Scale");
//    pool_factory->RegisterComponent<Rotation>("Rotation");
//    pool_factory->RegisterComponent<Velocity>("Velocity");
//    pool_factory->RegisterComponent<CircleCollider>("CircleCollider");
//
//    pool_factory->RegisterComponent<Sprite>("Sprite");
//    pool_factory->RegisterComponent<Tags>("Tags");
//
//    PoolArchetype metaball_pool_archetype;
//
//    Tags* metaball_tags = new Tags;
//    metaball_tags->tagSet_.insert("Metaball");
//    metaball_pool_archetype.poolComponents_["Tags"] = metaball_tags;
//
//    Sprite* metaball_sprite = new Sprite;
//    metaball_sprite->layer_ = 0;
//    metaball_sprite->texture_ = std::string("Test32");
//    metaball_pool_archetype.poolComponents_["Sprite"] = metaball_sprite;
//
//    metaball_pool_archetype.objectComponents_.push_back("Position");
//    metaball_pool_archetype.objectComponents_.push_back("Scale");
//    metaball_pool_archetype.objectComponents_.push_back("Rotation");
//    metaball_pool_archetype.objectComponents_.push_back("Velocity");
//    metaball_pool_archetype.objectComponents_.push_back("CircleCollider");
//
//    metaball_pool = pool_factory->CreatePool(metaball_pool_archetype, num_metaballs);
//
//    delete metaball_tags;
//    delete metaball_sprite;
//
//    creation_system = new CreationSystem;
//    collision_system = new CollisionSystem;
//    movement_system = new MovementSystem;
//    draw_system = new DrawSystem;
//
//    creation_system->Subscribe(metaball_pool);   
//    collision_system->Subscribe(metaball_pool);  
//    movement_system->Subscribe(metaball_pool);   
//    draw_system->Subscribe(metaball_pool);       
//
//    metaball_component_map = new ObjectComponentMap;
//    metaball_archetype = new ObjectArchetype;
//
//    metaball_archetype->objectComponents_ = metaball_component_map;
//    metaball_archetype->index_ = 0;
//
//    metaball_position = new Position;         metaball_position->Allocate(1);
//    metaball_scale = new Scale;               metaball_scale->Allocate(1);
//    metaball_rotation = new Rotation;         metaball_rotation->Allocate(1);
//    metaball_velocity = new Velocity;         metaball_velocity->Allocate(1);
//    metaball_collider = new CircleCollider;   metaball_collider->Allocate(1);
//
//    metaball_position->data_->position_.x = 640.0f;
//    metaball_position->data_->position_.y = 600.0f;
//
//    metaball_scale->data_->dimensions_.x = 16.0f;
//    metaball_scale->data_->dimensions_.y = 16.0f;
//
//    metaball_rotation->data_->angle_ = 0.0f;
//
//    metaball_velocity->data_->velocity_.x = 0.0f;
//    metaball_velocity->data_->velocity_.y = 0.0f;
//
//    metaball_collider->data_->radius_ = 16.0f;
//
//    (*metaball_component_map)["Position"] = metaball_position;
//    (*metaball_component_map)["Scale"] = metaball_scale;
//    (*metaball_component_map)["Rotation"] = metaball_rotation;
//    (*metaball_component_map)["Velocity"] = metaball_velocity;
//    (*metaball_component_map)["CircleCollider"] = metaball_collider;
//
//    rng = new Random;
//
//    // manually creating objects for now
//    for (unsigned i = 0; i < num_metaballs; i++)
//    {
//      metaball_position->data_->position_.x = rng->RangeFloat(200.0f, 1080.0f);
//      metaball_position->data_->position_.y = rng->RangeFloat(200.0f, 520.0f);
//      
//      float angle = glm::radians(rng->RangeFloat(0, 360.0f));
//      metaball_velocity->data_->velocity_.x = 3.0f * glm::cos(angle);
//      metaball_velocity->data_->velocity_.y = 3.0f * glm::sin(angle);
//
//      float scale = rng->RangeFloat(64.0f, 128.0f);
//      metaball_scale->data_->dimensions_.x = scale;
//      metaball_scale->data_->dimensions_.y = scale;
//      metaball_collider->data_->radius_ = scale / 2.0f;
//
//      creation_system->CreateObject(*metaball_archetype, metaball_pool);
//    }
//
//    draw_sprites = true;
//  }
//
//  void GSMetaballs::Update()
//  {
//    if (Engine::Input().KeyTriggered(KEY_D))
//    {
//      draw_sprites = !draw_sprites;
//    }
//    
//    movement_system->Update();
//
//    collision_system->Update();
//
//    CalculateGridValues();
//
//    CalculateCellValues();
//
//    CreateMesh();
//
//    DrawMesh();
//
//    if (draw_sprites)
//      draw_system->Update();
//  }
//
//  void GSMetaballs::Exit()
//  {
//    delete rng;
//
//    delete metaball_collider;
//    delete metaball_velocity;
//    delete metaball_rotation;
//    delete metaball_scale;
//    delete metaball_position;
//
//    delete metaball_archetype;
//    delete metaball_component_map;
//
//    delete draw_system;
//    delete movement_system;
//    delete collision_system;
//    delete creation_system;
//
//    delete metaball_pool;
//
//    delete pool_factory;
//  }
//
//  void GSMetaballs::CalculateGridValues()
//  {
//    Position* metaball_positions = static_cast<Position*>(metaball_pool->objectComponents_.at("Position"));
//    CircleCollider* metaball_radii = static_cast<CircleCollider*>(metaball_pool->objectComponents_.at("CircleCollider"));
//
//    // for each point on the 2D grid, calculate scalar field "value" based on contributions from all metaballs
//    for (unsigned i = 0; i < num_grid_points_x; ++i)
//    {
//      for (unsigned j = 0; j < num_grid_points_y; ++j)
//      {
//        float& grid_value = grid_values[i][j];
//
//        // initially set this grid point's value to zero
//        grid_value = 0.0f;
//
//        // if a grid point lies on any of the 4 borders of the grid, leave its value as
//        // zero (this ensures the metaball's surface stays within the screen bounds)
//        if (i == 0 || j == 0 || i == num_grid_points_x - 1 || j == num_grid_points_y - 1)
//          continue;
//
//        // world coordinates of grid point
//        glm::vec2 grid_position;
//
//        grid_position.x = i * 1280.0f / num_cells_x;
//        grid_position.y = j * 720.0f / num_cells_y;
//
//        // calculate value contribution from each metaball; overall value is >1 if grid point is inside at least one metaball
//        for (unsigned n = 0; n < num_metaballs; ++n)
//        {
//          float mb_radius = metaball_radii->data_[n].radius_;
//          glm::vec2 mb_position = metaball_positions->data_[n].position_;
//
//          float delta_x_sq = (mb_position.x - grid_position.x) * (mb_position.x - grid_position.x);
//          float delta_y_sq = (mb_position.y - grid_position.y) * (mb_position.y - grid_position.y);
//
//          float denominator = (delta_x_sq + delta_y_sq);
//
//          if (denominator < 0.00001f)
//            denominator = 0.00001f;
//
//          grid_value += mb_radius * mb_radius / denominator;
//        }
//      }
//    }
//  }
//
//  void GSMetaballs::CalculateCellValues()
//  {
//    // each cell has 4 grid points; figure out which of those points are within our metaball group
//    // note: a grid point is within the metaball group if its value is greater than 1.0f
//    for (unsigned i = 0; i < num_cells_x; ++i)
//    {
//      for (unsigned j = 0; j < num_cells_y; ++j)
//      {
//        unsigned& cell_value = cell_values[i][j];
//
//        cell_value = 0;
//
//        // 0th bit is set if bottom left grid point is within metaball group
//        if (grid_values[i][j] > 1.0f)
//          cell_value |= 1;
//
//        // 1st bit is set if bottom right grid point is within metaball group
//        if (grid_values[i + 1][j] > 1.0f)
//          cell_value |= 1 << 1;
//
//        // 2nd bit is set if top right grid point is within metaball group
//        if (grid_values[i + 1][j + 1] > 1.0f)
//          cell_value |= 1 << 2;
//
//        // 3rd bit is set if top left grid point is within metaball group
//        if (grid_values[i][j + 1] > 1.0f)
//          cell_value |= 1 << 3;
//      }
//    }
//  }
//
//  void GSMetaballs::CreateMesh()
//  {
//    vertices.clear();
//
//    glm::vec2 vertex_position;
//
//    float cell_width = 1280.0f / num_cells_x;
//    float cell_height = 720.0f / num_cells_y;
//
//    // determine whether each grid cell contains part of the mesh edge
//    for (unsigned i = 0; i < num_cells_x; ++i)
//    {
//      for (unsigned j = 0; j < num_cells_y; ++j)
//      {
//        // lookup table magic: determines which edges of the grid cell are intersected by 
//        // mesh edge based on which grid vertices are inside or outside metaball group
//        char* cell_array = vertex_locations[cell_values[i][j]];
//        
//        // if top edge is intersected, figure out where and add vertex location to mesh
//        if (cell_array[0])
//        {
//          float val1 = grid_values[i][j + 1];
//          float val2 = grid_values[i + 1][j + 1];
//
//          float weight;
//          
//          if ((val2 - val1) * (val2 - val1) < 0.00001f * 0.00001f)
//          {
//            weight = 0.5f;
//          }
//          else
//          {
//            weight = (1.0f - val1) / (val2 - val1);
//          }
//
//          vertex_position.x = i * cell_width + cell_width * weight;
//          vertex_position.y = j * cell_height + cell_height;
//
//          vertices.push_back(vertex_position);
//        }
//
//        // if right edge is intersected, figure out where and add vertex location to mesh
//        if (cell_array[1])
//        {
//          float val1 = grid_values[i + 1][j];
//          float val2 = grid_values[i + 1][j + 1];
//
//          float weight;
//
//          if ((val2 - val1) * (val2 - val1) < 0.00001f * 0.00001f)
//          {
//            weight = 0.5f;
//          }
//          else
//          {
//            weight = (1.0f - val1) / (val2 - val1);
//          }
//          
//          vertex_position.x = i * cell_width + cell_width;
//          vertex_position.y = j * cell_height + cell_height * weight;
//
//          vertices.push_back(vertex_position);
//        }
//
//        // if bottom edge is intersected, figure out where and add vertex location to mesh
//        if (cell_array[2])
//        {
//          float val1 = grid_values[i][j];
//          float val2 = grid_values[i + 1][j];
//
//          float weight;
//
//          if ((val2 - val1) * (val2 - val1) < 0.00001f * 0.00001f)
//          {
//            weight = 0.5f;
//          }
//          else
//          {
//            weight = (1.0f - val1) / (val2 - val1);
//          }
//          
//          vertex_position.x = i * cell_width + cell_width * weight;
//          vertex_position.y = j * cell_height;
//
//          vertices.push_back(vertex_position);
//        }
//
//        // if left edge is intersected, figure out where and add vertex location to mesh
//        if (cell_array[3])
//        {
//          float val1 = grid_values[i][j];
//          float val2 = grid_values[i][j + 1];
//
//          float weight;
//
//          if ((val2 - val1) * (val2 - val1) < 0.00001f * 0.00001f)
//          {
//            weight = 0.5f;
//          }
//          else
//          {
//            weight = (1.0f - val1) / (val2 - val1);
//          }
//          
//          vertex_position.x = i * cell_width;
//          vertex_position.y = j * cell_height + cell_height * weight;
//
//          vertices.push_back(vertex_position);
//        }
//      }
//    }
//
//    scales.resize(vertices.size(), glm::vec2(2.0f));
//    rotations.resize(vertices.size(), 0.0f);
//  }
//
//  void GSMetaballs::DrawMesh()
//  {
//    // note: the "mesh" isn't really a mesh, I'm just drawing a small bullet sprite on each vertex that exists :)
//    TestRenderer::Instance().DrawInstanced(vertices.data(), rotations.data(), scales.data(), vertices.size(), "Test32");
//  }
//}