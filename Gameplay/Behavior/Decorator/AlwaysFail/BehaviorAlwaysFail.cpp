/* ======================================================================== */
/*!
 * \file            BehaviorAlwaysFail.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "BehaviorAlwaysFail.hpp"

namespace Barrage
{
  namespace Behavior
  {
    AlwaysFail::AlwaysFail() : BehaviorNode("AlwaysFail", BehaviorNodeType::Decorator) {};

    std::shared_ptr<BehaviorNode> AlwaysFail::Clone() const
    {
      return std::make_shared<AlwaysFail>(*this);
    }

    void AlwaysFail::OnBegin(BehaviorNodeInfo& info)
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

    BehaviorState AlwaysFail::Execute(BehaviorNodeInfo& info)
    {
      return result_;
    }

    void AlwaysFail::OnChildFinish(BehaviorNodeInfo& info, BehaviorState::State result, int childNodeIndex)
    {
      result_ = BehaviorState::Failure();
    }
  }
}