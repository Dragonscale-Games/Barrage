/* ======================================================================== */
/*!
 * \file            BehaviorRepeat.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "BehaviorRepeat.hpp"

namespace Barrage
{
  namespace Behavior
  {
    RepeatData::RepeatData() : 
      numIterations_(1) 
    {
    }
    
    RepeatArrayElement::RepeatArrayElement() : 
      currentIterations_(0) 
    {
    }
    
    Repeat::Repeat() : BehaviorNodeTA<RepeatData, RepeatArrayElement>("Repeat", BehaviorNodeType::Decorator) {};

    std::shared_ptr<BehaviorNode> Repeat::Clone() const
    {
      return std::make_shared<Repeat>(*this);
    }

    void Repeat::OnBegin(BehaviorNodeInfo& info)
    {
      if (childIndices_.empty())
      {
        result_ = BehaviorState::Success();
      }
      else
      {
        result_ = BehaviorState::Transfer(childIndices_[0]);
      }
    }

    BehaviorState Repeat::Execute(BehaviorNodeInfo& info)
    {
      return result_;
    }

    void Repeat::OnChildFinish(BehaviorNodeInfo& info, BehaviorState::State result, int childNodeIndex)
    {
      unsigned& currentIterations_ = dataArray_.Data(info.objectIndex_).currentIterations_;
      
      currentIterations_++;

      if (result == BehaviorState::State::Failure)
      {
        result_ = BehaviorState::Failure();
      }
      else if (currentIterations_ < data_.numIterations_)
      {
        result_ = BehaviorState::Transfer(childIndices_[0]);
      }
      else
      {
        result_ = BehaviorState::Success();
      }
    }

    void Repeat::Reflect()
    {
      rttr::registration::class_<Behavior::RepeatData>("RepeatData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("numIterations", &Behavior::RepeatData::numIterations_)
        ;
    }
  }
}