/* ======================================================================== */
/*!
 * \file            BehaviorAlwaysSucceed.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "BehaviorAlwaysSucceed.hpp"

namespace Barrage
{
  namespace Behavior
  {
    AlwaysSucceed::AlwaysSucceed() : BehaviorNode("AlwaysSucceed", BehaviorNodeType::Decorator) {};

    std::shared_ptr<BehaviorNode> AlwaysSucceed::Clone() const
    {
      return std::make_shared<AlwaysSucceed>(*this);
    }

    void AlwaysSucceed::OnBegin(BehaviorNodeInfo& info)
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

    BehaviorState AlwaysSucceed::Execute(BehaviorNodeInfo& info)
    {
      return result_;
    }

    void AlwaysSucceed::OnChildFinish(BehaviorNodeInfo& info, BehaviorState::State result, int childNodeIndex)
    {
      result_ = BehaviorState::Success();
    }
  }
}