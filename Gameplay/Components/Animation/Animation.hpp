/* ======================================================================== */
/*!
 * \file            Animation.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here>

 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Animation_BARRAGE_H
#define Animation_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/Component.hpp"
#include "Renderer/RendererTypes.hpp"

#include <string>
#include <vector>

namespace Barrage
{
  struct AnimationState
  {
    unsigned ticksElapsed_;           //!< Number of ticks remaining in the animation
    unsigned animationSequenceIndex_; //!< Represents the currently playing animation sequence
    unsigned frameIndex_;             //!< Represents the current frame of the animation sequence

    AnimationState();
  };

  struct AnimationSequence
  {
    std::vector<unsigned> spriteFrames_; //!< The individual frames of the animation
    std::vector<TextureUV> frameUVs_;    //!< Texture UVs corresponding to the chosen animation frames
    unsigned ticksPerFrame_;
    bool loops_;
    std::string name_;

    AnimationSequence();
  };

  //! Component that controls spritesheet animation
  class Animation
  {
    public:
      std::vector<AnimationSequence> animationSequences_; //!< Animation sequences (idle, run, jump, etc)
      ComponentArrayT<AnimationState> animationStates_;   //!< Per-object animation states

      Animation();

      static void Reflect();
  };

  typedef ComponentT<Animation> AnimationComponent;

  template <>
  void ComponentT<Animation>::SetCapacity(unsigned capacity);

  template <>
  void ComponentT<Animation>::HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex);
}

////////////////////////////////////////////////////////////////////////////////
#endif // Animation_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////