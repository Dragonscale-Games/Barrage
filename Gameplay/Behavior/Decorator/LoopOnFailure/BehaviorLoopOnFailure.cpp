/* ======================================================================== */
/*!
 * \file            BehaviorLoopOnFailure.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "BehaviorLoopOnFailure.hpp"

namespace Barrage
{
  namespace Behavior
  {
    LoopOnFailure::LoopOnFailure() : BehaviorNode("LoopOnFailure", BehaviorNodeType::Decorator) {};

    std::shared_ptr<BehaviorNode> LoopOnFailure::Clone() const
    {
      return std::make_shared<LoopOnFailure>(*this);
    }

    void LoopOnFailure::OnBegin(BehaviorNodeInfo& info)
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

    BehaviorState LoopOnFailure::Execute(BehaviorNodeInfo& info)
    {
      return result_;
    }

    void LoopOnFailure::OnChildFinish(BehaviorNodeInfo& info, BehaviorState::State result, int childNodeIndex)
    {
      if (result == BehaviorState::State::Failure)
      {
        result_ = BehaviorState::Transfer(childIndices_[0]);
      }
      else
      {
        result_ = BehaviorState::Success();
      }
    }
  }
}