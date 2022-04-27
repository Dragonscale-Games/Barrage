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
    systemComponents_.push_back("PositionArray");
    systemComponents_.push_back("ScaleArray");
    systemComponents_.push_back("RotationArray");
    systemComponents_.push_back("Sprite");
  }
  
  void DrawSystem::Subscribe(Pool* pool)
  {
    if (PoolMatchesSystem(pool))
    {
      Sprite* pool_sprite = dynamic_cast<Sprite*>(pool->sharedComponents_.at("Sprite"));
      
      pools_.insert(std::pair<unsigned, Pool*>(pool_sprite->layer_, pool));
    }
  }

  void DrawSystem::Draw()
  {
    for (auto it = pools_.begin(); it != pools_.end(); ++it)
    {
      Pool* pool = it->second;

      PositionArray& position_array = pool->GetComponentArray<PositionArray>("PositionArray");
      ScaleArray& scale_array = pool->GetComponentArray<ScaleArray>("ScaleArray");
      RotationArray& rotation_array = pool->GetComponentArray<RotationArray>("RotationArray");

      glm::vec2* positions = reinterpret_cast<glm::vec2*>(position_array.data_);
      glm::vec2* scales = reinterpret_cast<glm::vec2*>(scale_array.data_);
      float* rotations = reinterpret_cast<float*>(rotation_array.data_);

      Sprite& pool_sprite = pool->GetSharedComponent<Sprite>("Sprite");

      TestRenderer::Instance().DrawInstanced(positions, rotations, scales, pool->activeObjects_, pool_sprite.texture_);
    }
  }
}