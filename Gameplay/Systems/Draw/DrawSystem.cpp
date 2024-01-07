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

#include "Engine.hpp"

#include "Components/Sprite.hpp"
#include "ComponentArrays/ColorTintArray.hpp"
#include "ComponentArrays/PositionArray.hpp"
#include "ComponentArrays/RotationArray.hpp"
#include "ComponentArrays/ScaleArray.hpp"
#include "ComponentArrays/TextureUVArray.hpp"

namespace Barrage
{
  DrawSystem::DrawSystem() :
    System(),
    drawPools_()
  {
    PoolType basic_sprite_type;
    basic_sprite_type.AddComponentArray("ColorTint");
    basic_sprite_type.AddComponentArray("Position");
    basic_sprite_type.AddComponentArray("Scale");
    basic_sprite_type.AddComponentArray("Rotation");
    basic_sprite_type.AddComponentArray("TextureUV");
    basic_sprite_type.AddComponent("Sprite");
    poolTypes_["Basic 2D Sprite Pools"] = basic_sprite_type;
  }
  
  void DrawSystem::Subscribe(Space& space, Pool* pool)
  {
    UNREFERENCED(space);
    
    if (poolTypes_["Basic 2D Sprite Pools"].MatchesPool(pool))
    {
      Sprite& pool_sprite = pool->GetComponent<Sprite>("Sprite").Data();
      
      drawPools_[pool_sprite.layer_].push_back(pool);

      Engine::Get().Graphics().ReserveInstances(pool->GetCapacity());
    }
  }

  void DrawSystem::Unsubscribe(Space& space, Pool* pool)
  {
    UNREFERENCED(space);
    
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
    Renderer& renderer = Engine::Get().Graphics();

    for (auto it = drawPools_.begin(); it != drawPools_.end(); ++it)
    {
      std::vector<Pool*>& pool_group = drawPools_[it->first];
      
      for (auto jt = pool_group.begin(); jt != pool_group.end(); ++jt)
      {
        Pool* pool = *jt;

        PositionArray& position_array = pool->GetComponentArray<Position>("Position");
        ScaleArray& scale_array = pool->GetComponentArray<Scale>("Scale");
        RotationArray& rotation_array = pool->GetComponentArray<Rotation>("Rotation");
        ColorTintArray& color_tint_array = pool->GetComponentArray<ColorTint>("ColorTint");
        TextureUVArray& texture_uv_array = pool->GetComponentArray<TextureUV>("TextureUV");

        Sprite& pool_sprite = pool->GetComponent<Sprite>("Sprite").Data();

        renderer.DrawInstanced(
          position_array.GetRaw(),
          rotation_array.GetRaw(),
          scale_array.GetRaw(),
          color_tint_array.GetRaw(),
          texture_uv_array.GetRaw(),
          pool->ActiveObjectCount(), 
          pool_sprite.texture_
        );
      }
    }
  }
}