/* ======================================================================== */
/*!
 * \file            BehaviorSequence.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "BehaviorSequence.hpp"

namespace Barrage
{
  namespace Behavior
  {
    BehaviorState Sequence::result_ = BehaviorState::Success();
    
    Sequence::Sequence() : BehaviorNode("Sequence", BehaviorNodeType::Composite) {};

    std::shared_ptr<BehaviorNode> Sequence::Clone() const
    {
      return std::make_shared<Sequence>(*this);
    }

    void Sequence::OnBegin(BehaviorNodeInfo& info)
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

    BehaviorState Sequence::Execute(BehaviorNodeInfo& info)
    {
      return result_;
    }

    void Sequence::OnChildFinish(BehaviorNodeInfo& info, BehaviorState::State result, int childIndex)
    {
      if (result == BehaviorState::State::Failure)
      {
        result_ = BehaviorState::Failure();
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

      result_ = BehaviorState::Success();
    }
  }
}