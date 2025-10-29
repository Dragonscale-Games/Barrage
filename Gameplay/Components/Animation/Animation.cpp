/* ======================================================================== */
/*!
 * \file            Animation.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "Animation.hpp"

namespace Barrage
{
  AnimationState::AnimationState() :
    ticksElapsed_(0),
    animationSequenceIndex_(0),
    frameIndex_(0)
  {
  }

  AnimationSequence::AnimationSequence() :
    spriteFrames_(),
    frameUVs_(),
    ticksPerFrame_(1),
    loops_(true),
    name_("<untitled>")
  {
  }

  Animation::Animation() :
    animationSequences_(),
    animationStates_()
  {
  }

  void Animation::Reflect()
  {
    rttr::registration::class_<AnimationSequence>("AnimationSequence")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("spriteFrames", &AnimationSequence::spriteFrames_)
      .property("ticksPerFrame", &AnimationSequence::ticksPerFrame_)
      .property("loops", &AnimationSequence::loops_)
      .property("name", &AnimationSequence::name_)
      ;

    rttr::registration::class_<Animation>("Animation")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("animationSequences", &Animation::animationSequences_)
      ;
  }

  template <>
  void ComponentT<Animation>::SetCapacity(unsigned capacity)
  {
    data_.animationStates_.SetCapacity(capacity);

    for (unsigned i = 0; i < capacity; ++i)
    {
      data_.animationStates_.Data(i) = AnimationState();
    }
  }

  template <>
  void ComponentT<Animation>::HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex)
  {
    unsigned numAliveObjects = data_.animationStates_.HandleDestructions(destructionArray, writeIndex, endIndex);

    for (unsigned i = numAliveObjects; i < endIndex; ++i)
    {
      data_.animationStates_.Data(i) = AnimationState();;
    }
  }
}