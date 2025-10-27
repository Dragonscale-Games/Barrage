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

#include "Components/Animation/Animation.hpp"
#include "Components/Sprite/Sprite.hpp"
#include "ComponentArrays/ColorTint/ColorTintArray.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"
#include "ComponentArrays/Rotation/RotationArray.hpp"
#include "ComponentArrays/Scale/ScaleArray.hpp"
#include "ComponentArrays/TextureUV/TextureUVArray.hpp"

namespace Barrage
{
  static const std::string BASIC_2D_SPRITE_POOLS("Basic 2D Sprite Pools");
  static const std::string ANIMATED_POOLS("Animated Pools");
  
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
    poolTypes_[BASIC_2D_SPRITE_POOLS] = basic_sprite_type;

    PoolType animated_pool_type;
    animated_pool_type.AddComponentArray("TextureUV");
    animated_pool_type.AddComponent("Animation");
    animated_pool_type.AddComponent("Sprite");
    poolTypes_[ANIMATED_POOLS] = animated_pool_type;
  }
  
  void DrawSystem::Subscribe(Space& space, Pool* pool)
  {
    UNREFERENCED(space);
    
    if (poolTypes_[BASIC_2D_SPRITE_POOLS].MatchesPool(pool))
    {
      Sprite& pool_sprite = pool->GetComponent<Sprite>("Sprite").Data();
      
      drawPools_[pool_sprite.layer_].push_back(pool);

      Engine::Get().Graphics().ReserveInstances(pool->GetCapacity());
    }

    if (poolTypes_[ANIMATED_POOLS].MatchesPool(pool))
    {
      Animation& pool_animation = pool->GetComponent<Animation>("Animation").Data();
      Sprite& pool_sprite = pool->GetComponent<Sprite>("Sprite").Data();
      std::vector<AnimationSequence>& animation_sequences = pool_animation.animationSequences_;

      if (pool_sprite.cols_ == 0)
      {
        pool_sprite.cols_ = 1;
      }

      if (pool_sprite.rows_ == 0)
      {
        pool_sprite.rows_ = 1;
      }

      if (!animation_sequences.empty())
      {
        for (auto it = pool_animation.animationSequences_.begin(); it != pool_animation.animationSequences_.end(); ++it)
        {
          AnimationSequence& animation_sequence = *it;
          std::vector<unsigned>& sprite_frames = animation_sequence.spriteFrames_;

          if (sprite_frames.empty())
          {
            sprite_frames.push_back(0);
          }

          if (animation_sequence.ticksPerFrame_ == 0)
          {
            animation_sequence.ticksPerFrame_ = 1;
          }

          for (auto jt = sprite_frames.begin(); jt != sprite_frames.end(); ++jt)
          {
            unsigned sprite_cols = pool_sprite.cols_;
            unsigned sprite_rows = pool_sprite.rows_;
            unsigned total_frames = sprite_cols * sprite_rows;
            unsigned frame = *jt % total_frames;

            TextureUV textureUV;

            textureUV.uMin_ = static_cast<float>(frame % sprite_cols) / sprite_cols;
            textureUV.vMin_ = static_cast<float>((sprite_rows - 1) - frame / sprite_cols) / sprite_rows;
            textureUV.uSize_ = 1.0f / sprite_cols;
            textureUV.vSize_ = 1.0f / sprite_rows;

            animation_sequence.frameUVs_.push_back(textureUV);
          }
        }
        
        poolGroups_[ANIMATED_POOLS].push_back(pool);
      }
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

    System::Unsubscribe(space, pool);
  }

  void DrawSystem::Update()
  {
    UpdatePoolGroup(ANIMATED_POOLS, UpdateAnimations);
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

  void DrawSystem::UpdateAnimations(Space& space, Pool& pool)
  {
    Animation& pool_animation = pool.GetComponent<Animation>("Animation").Data();
    TextureUVArray& texture_uv_array = pool.GetComponentArray<TextureUV>("TextureUV");

    unsigned num_objects = pool.ActiveObjectCount();

    for (unsigned i = 0; i < num_objects; ++i)
    {
      AnimationState& animation_state = pool_animation.animationStates_.Data(i);
      AnimationSequence& animation_sequence = pool_animation.animationSequences_.at(animation_state.animationSequenceIndex_);
      size_t num_frames = animation_sequence.frameUVs_.size();

      if (animation_state.frameIndex_ < num_frames)
      {
        texture_uv_array.Data(i) = animation_sequence.frameUVs_.at(animation_state.frameIndex_);

        if (animation_state.ticksElapsed_ >= animation_sequence.ticksPerFrame_)
        {
          ++animation_state.frameIndex_;
          animation_state.ticksElapsed_ = 0;

          if (animation_state.frameIndex_ == num_frames && animation_sequence.loops_)
          {
            animation_state.frameIndex_ = 0;
          }
        }
        else
        {
          ++animation_state.ticksElapsed_;
        }
      }
    }
  }
}