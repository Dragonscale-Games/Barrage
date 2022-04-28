/* ======================================================================== */
/*!
 * \file            GS_Waves.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <description>

 */
/* ======================================================================== */

#include "stdafx.h"
#include "GSWaves.hpp"

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
  GSWaves::GSWaves() : GameState(Enter, Update, Exit)
  {
  }

  void GSWaves::Enter()
  {
    unsigned NUM_WAVEDOTS = 5000;

    PoolArchetype* wavedot_pool_archetype = new PoolArchetype;

    Tags* wavedot_tags = new Tags;
    wavedot_tags->tagSet_.insert("WaveDot");
    wavedot_pool_archetype->poolComponents_["Tags"] = wavedot_tags;

    Sprite* wavedot_sprite = new Sprite;
    wavedot_sprite->layer_ = 0;
    wavedot_sprite->texture_ = std::string("Test32");
    wavedot_pool_archetype->poolComponents_["Sprite"] = wavedot_sprite;

    Timer* wavedot_timer = new Timer;
    wavedot_pool_archetype->poolComponents_["Timer"] = wavedot_timer;

    wavedot_pool_archetype->objectComponents_.push_back("Position");
    wavedot_pool_archetype->objectComponents_.push_back("Scale");
    wavedot_pool_archetype->objectComponents_.push_back("Rotation");

    Engine::Objects().AddPoolArchetype("WaveDot Pool Archetype", wavedot_pool_archetype);
    Engine::Objects().CreatePool("WaveDot Pool", "WaveDot Pool Archetype", NUM_WAVEDOTS);

    ObjectArchetype* wavedot_object_archetype = new ObjectArchetype;
    ObjectComponentMap& wavedot_component_map = wavedot_object_archetype->objectComponents_;

    Position* wavedot_position = new Position;   wavedot_position->Allocate(1);
    Scale* wavedot_scale = new Scale;            wavedot_scale->Allocate(1);
    Rotation* wavedot_rotation = new Rotation;   wavedot_rotation->Allocate(1);

    wavedot_position->data_->position_.x = 0.0f;
    wavedot_position->data_->position_.y = 360.0f;

    wavedot_scale->data_->dimensions_.x = 2.0f;
    wavedot_scale->data_->dimensions_.y = 2.0f;

    wavedot_rotation->data_->angle_ = 0.0f;

    wavedot_component_map["Position"] = wavedot_position;
    wavedot_component_map["Scale"] = wavedot_scale;
    wavedot_component_map["Rotation"] = wavedot_rotation;

    Engine::Objects().AddObjectArchetype("WaveDot Object Archetype", wavedot_object_archetype);

    for (unsigned i = 0; i < NUM_WAVEDOTS; ++i)
    {
      wavedot_position->data_->position_.x = (1280.0f * i) / NUM_WAVEDOTS;

      Engine::Objects().CreateObject("WaveDot Pool", "WaveDot Object Archetype");
    }
  }

  void GSWaves::Update()
  {

  }

  void GSWaves::Exit()
  {
    Engine::Objects().DeletePool("WaveDot Pool");
  }
}