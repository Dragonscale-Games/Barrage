/* ======================================================================== */
/*!
 * \file            BehaviorLoopOnSuccess.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "BehaviorLoopOnSuccess.hpp"

namespace Barrage
{
  namespace Behavior
  {
    LoopOnSuccess::LoopOnSuccess() : BehaviorNode("LoopOnSuccess", BehaviorNodeType::Decorator) {};

    std::shared_ptr<BehaviorNode> LoopOnSuccess::Clone() const
    {
      return std::make_shared<LoopOnSuccess>(*this);
    }

    void LoopOnSuccess::OnBegin(BehaviorNodeInfo& info)
    {
      if (childIndices_.empty())
      {
        result_ = BehaviorState::Failure();
      }
      else
      {
        result_ = BehaviorState::Transfer(childIndices_[0]);
      }
    }

    BehaviorState LoopOnSuccess::Execute(BehaviorNodeInfo& info)
    {
      return result_;
    }

    void LoopOnSuccess::OnChildFinish(BehaviorNodeInfo& info, BehaviorState::State result, int childNodeIndex)
    {
      if (result == BehaviorState::State::Success)
      {
        result_ = BehaviorState::Transfer(childIndices_[0]);
      }
      else
      {
        result_ = BehaviorState::Failure();
      }
    }
  }
}