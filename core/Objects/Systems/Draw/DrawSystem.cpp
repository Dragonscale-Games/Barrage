/* ======================================================================== */
/*!
 * \file            DrawSystem.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 
 */
/* ======================================================================== */

#include "stdafx.h"
#include "DrawSystem.hpp"

#include <TempRenderer/TestRenderer.hpp>

namespace Barrage
{
  DrawSystem::DrawSystem() :
    System()
  {
    systemComponents_.push_back("Position");
    systemComponents_.push_back("Scale");
    systemComponents_.push_back("Rotation");
    systemComponents_.push_back("Sprite");
  }
  
  void DrawSystem::Subscribe(Pool* pool)
  {
    if (PoolMatchesSystem(pool))
    {
      Sprite* pool_sprite = dynamic_cast<Sprite*>(pool->poolComponents_.at("Sprite"));
      
      pools_.insert(std::pair<unsigned, Pool*>(pool_sprite->layer_, pool));
    }
  }

  void DrawSystem::Draw()
  {
    for (auto it = pools_.begin(); it != pools_.end(); ++it)
    {
      Pool* pool = it->second;

      Position* position_component = dynamic_cast<Position*>(pool->objectComponents_.at("Position"));
      Scale* scale_component = dynamic_cast<Scale*>(pool->objectComponents_.at("Scale"));
      Rotation* rotation_component = dynamic_cast<Rotation*>(pool->objectComponents_.at("Rotation"));

      glm::vec2* positions = reinterpret_cast<glm::vec2*>(position_component->data_);
      glm::vec2* scales = reinterpret_cast<glm::vec2*>(scale_component->data_);
      float* rotations = reinterpret_cast<float*>(rotation_component->data_);

      Sprite* pool_sprite = dynamic_cast<Sprite*>(pool->poolComponents_.at("Sprite"));

      TestRenderer::Instance().DrawInstanced(positions, rotations, scales, pool->activeObjects_, pool_sprite->texture_);
    }
  }
}