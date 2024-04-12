/* ======================================================================== */
/*!
 * \file            BehaviorParallelSequence.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "BehaviorParallelSequence.hpp"
#include "Objects/Behavior/BehaviorTree.hpp"

namespace Barrage
{
  namespace Behavior
  {
    ParallelSequence::ParallelSequence() : BehaviorNodeTA<Dummy, ParallelNodeArrayElement>("ParallelSequence", BehaviorNodeType::Parallel) {};

    std::shared_ptr<BehaviorNode> ParallelSequence::Clone() const
    {
      return std::make_shared<ParallelSequence>(*this);
    }

    void ParallelSequence::OnBegin(BehaviorNodeInfo& info)
    {
      ParallelNode::OnBegin(childIndices_, dataArray_.Data(info.objectIndex_));
    }

    BehaviorState ParallelSequence::Execute(BehaviorNodeInfo& info)
    {
      ParallelNodeArrayElement& element = dataArray_.Data(info.objectIndex_);

      ParallelNode::Execute(childIndices_, element, info);

      bool allSuccess = true;

      for (size_t i = 0; i < MAX_PARALLEL_NODE_CHILDREN; ++i)
      {
        int& nodeIndex = element.nodeIndices_[i];

        if (nodeIndex == PARALLEL_CHILD_SUCCESS)
        {
          // do nothing
        }
        else if (nodeIndex == PARALLEL_CHILD_FAILURE)
        {
          allSuccess = false;
        }
        else
        {
          return BehaviorState::Running();
        }
      }

      if (allSuccess)
      {
        return BehaviorState::Success();
      }
      else
      {
        return BehaviorState::Failure();
      }
    }
  }
}