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
    basic_sprite_type.AddComponentArray("Position");
    basic_sprite_type.AddComponentArray("Scale");
    basic_sprite_type.AddComponentArray("Rotation");
    basic_sprite_type.AddSharedComponent("Sprite");
    basic_sprite_type.AddComponentArray("TextureSpace");
    poolTypes_[BASIC_2D_SPRITE_POOLS] = basic_sprite_type;
  }
  
  void DrawSystem::Subscribe(Pool* pool)
  {
    if (poolTypes_[BASIC_2D_SPRITE_POOLS].MatchesPool(pool))
    {
      Sprite& pool_sprite = pool->GetSharedComponent<Sprite>("Sprite")->Data();
      
      pools_[pool_sprite.layer_].push_back(pool);
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

        PositionArray& position_array = *pool->GetComponentArray<Position>("Position");
        ScaleArray& scale_array = *pool->GetComponentArray<Scale>("Scale");
        RotationArray& rotation_array = *pool->GetComponentArray<Rotation>("Rotation");
        TextureSpaceArray& tex_space_array = *pool->GetComponentArray<TextureSpace>("TextureSpace");

        glm::vec2* positions = reinterpret_cast<glm::vec2*>(position_array.data_);
        glm::vec2* scales = reinterpret_cast<glm::vec2*>(scale_array.data_);
        glm::vec4* tex_coords = reinterpret_cast<glm::vec4*>(tex_space_array.data_);
        float* rotations = reinterpret_cast<float*>(rotation_array.data_);

        Sprite& pool_sprite = pool->GetSharedComponent<Sprite>("Sprite")->Data();

        drawing.DrawInstancedQuad(
          pool->numActiveObjects_, 
          positions, scales, 
          rotations, tex_coords, pool_sprite.texture_.c_str());
      }
    }
  }
}