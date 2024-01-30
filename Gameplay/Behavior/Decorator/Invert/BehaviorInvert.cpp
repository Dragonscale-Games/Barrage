/* ======================================================================== */
/*!
 * \file            BehaviorInvert.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "BehaviorInvert.hpp"

namespace Barrage
{
  namespace Behavior
  {
    Invert::Invert() : BehaviorNode("Invert", BehaviorNodeType::Decorator) {};

    std::shared_ptr<BehaviorNode> Invert::Clone() const
    {
      return std::make_shared<Invert>(*this);
    }

    void Invert::OnBegin(BehaviorNodeInfo& info)
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

    BehaviorState Invert::Execute(BehaviorNodeInfo& info)
    {
      return result_;
    }

    void Invert::OnChildFinish(BehaviorNodeInfo& info, BehaviorState::State result, int childNodeIndex)
    {
      if (result == BehaviorState::State::Failure)
      {
        result_ = BehaviorState::Success();
      }
      else
      {
        result_ = BehaviorState::Failure();
      }
    }
  }
}