/* ======================================================================== */
/*!
 * \file            BehaviorSelector.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "BehaviorSelector.hpp"

namespace Barrage
{
  namespace Behavior
  {
    BehaviorState Selector::result_ = BehaviorState::Success();
    
    Selector::Selector() : BehaviorNode("Selector", BehaviorNodeType::Decorator) {};

    std::shared_ptr<BehaviorNode> Selector::Clone() const
    {
      return std::make_shared<Selector>(*this);
    }

    void Selector::OnBegin(BehaviorNodeInfo& info)
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

    BehaviorState Selector::Execute(BehaviorNodeInfo& info)
    {
      return result_;
    }

    void Selector::OnChildFinish(BehaviorNodeInfo& info, BehaviorState::State result, int childIndex)
    {
      if (result == BehaviorState::State::Success)
      {
        result_ = BehaviorState::Success();
        return;
      }

      size_t numChildren = childIndices_.size();

      for (size_t i = 1; i < numChildren; ++i)
      {
        if (childIndices_[i - 1] == childIndex)
        {
          result_ = BehaviorState::Transfer(childIndices_[i]);
          return;
        }
      }

      result_ = BehaviorState::Failure();
    }
  }
}