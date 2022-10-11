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

#include <Engine/Engine.hpp>

namespace Barrage
{
  static const unsigned BASIC_2D_SPRITE_POOLS = 0;
  
  DrawSystem::DrawSystem() :
    System()
  {
    PoolType basic_sprite_type;
    basic_sprite_type.AddComponentName("PositionArray");
    basic_sprite_type.AddComponentName("ScaleArray");
    basic_sprite_type.AddComponentName("RotationArray");
    basic_sprite_type.AddComponentName("Sprite");
    poolTypes_[BASIC_2D_SPRITE_POOLS] = basic_sprite_type;
  }
  
  void DrawSystem::Subscribe(Pool* pool)
  {
    if (poolTypes_[BASIC_2D_SPRITE_POOLS].MatchesPool(pool))
    {
      Sprite* pool_sprite = dynamic_cast<Sprite*>(pool->sharedComponents_.at("Sprite"));
      
      pools_[pool_sprite->layer_].push_back(pool);
    }
  }

  void DrawSystem::Draw()
  {
    GfxDraw2D& drawing = Engine::Instance->Drawing();

    for (auto it = pools_.begin(); it != pools_.end(); ++it)
    {
      std::vector<Pool*>& pool_group = pools_[it->first];
      
      for (auto jt = pool_group.begin(); jt != pool_group.end(); ++jt)
      {
        Pool* pool = *jt;

        PositionArray& position_array = *pool->GetComponentArray<PositionArray>("PositionArray");
        ScaleArray& scale_array = *pool->GetComponentArray<ScaleArray>("ScaleArray");
        RotationArray& rotation_array = *pool->GetComponentArray<RotationArray>("RotationArray");

        glm::vec2* positions = reinterpret_cast<glm::vec2*>(position_array.data_);
        glm::vec2* scales = reinterpret_cast<glm::vec2*>(scale_array.data_);
        float* rotations = reinterpret_cast<float*>(rotation_array.data_);

        Sprite& pool_sprite = *pool->GetSharedComponent<Sprite>("Sprite");

        drawing.DrawInstancedQuad(pool->size_, positions, scales, rotations, pool_sprite.texture_.c_str());
      }
    }
  }
}