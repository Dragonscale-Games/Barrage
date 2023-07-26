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
#include "Objects/Systems/DrawSystem.hpp"

#include <Engine/Engine.hpp>

#include "Components/Sprite.hpp"
#include "ComponentArrays/PositionArray.hpp"
#include "ComponentArrays/RotationArray.hpp"
#include "ComponentArrays/ScaleArray.hpp"

namespace Barrage
{
  DrawSystem::DrawSystem() :
    System(),
    drawPools_()
  {
    PoolType basic_sprite_type;
    basic_sprite_type.AddComponentArray("Position");
    basic_sprite_type.AddComponentArray("Scale");
    basic_sprite_type.AddComponentArray("Rotation");
    basic_sprite_type.AddComponent("Sprite");
    poolTypes_["Basic 2D Sprite Pools"] = basic_sprite_type;
  }
  
  void DrawSystem::Subscribe(Pool* pool)
  {
    if (poolTypes_["Basic 2D Sprite Pools"].MatchesPool(pool))
    {
      Sprite& pool_sprite = pool->GetComponent<Sprite>("Sprite")->Data();
      
      drawPools_[pool_sprite.layer_].push_back(pool);
    }
  }

  void DrawSystem::Unsubscribe(Pool* pool)
  {
    for (auto it = drawPools_.begin(); it != drawPools_.end(); ++it)
    {
      std::vector<Pool*>& pool_group = it->second;

      for (auto jt = pool_group.begin(); jt != pool_group.end(); /* iterator incremented in body */)
      {
        if (*jt == pool)
        {
          jt = pool_group.erase(jt);
        }
        else
        {
          ++jt;
        }
      }
    }
  }

  void DrawSystem::Draw()
  {
    Renderer& renderer = Engine::Instance->Graphics();

    for (auto it = drawPools_.begin(); it != drawPools_.end(); ++it)
    {
      std::vector<Pool*>& pool_group = drawPools_[it->first];
      
      for (auto jt = pool_group.begin(); jt != pool_group.end(); ++jt)
      {
        Pool* pool = *jt;

        PositionArray& position_array = *pool->GetComponentArray<Position>("Position");
        ScaleArray& scale_array = *pool->GetComponentArray<Scale>("Scale");
        RotationArray& rotation_array = *pool->GetComponentArray<Rotation>("Rotation");

        glm::vec2* positions = reinterpret_cast<glm::vec2*>(position_array.data_);
        glm::vec2* scales = reinterpret_cast<glm::vec2*>(scale_array.data_);
        float* rotations = reinterpret_cast<float*>(rotation_array.data_);

        Sprite& pool_sprite = pool->GetComponent<Sprite>("Sprite")->Data();

        renderer.DrawInstanced(positions, rotations, scales, pool->GetActiveObjectCount(), pool_sprite.texture_);
      }
    }
  }
}