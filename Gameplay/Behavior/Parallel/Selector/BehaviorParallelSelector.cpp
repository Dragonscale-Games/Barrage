/* ======================================================================== */
/*!
 * \file            BehaviorParallelSelector.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "BehaviorParallelSelector.hpp"
#include "Objects/Behavior/BehaviorTree.hpp"

namespace Barrage
{
  namespace Behavior
  {
    ParallelSelector::ParallelSelector() : BehaviorNodeTA<Dummy, ParallelNodeArrayElement>("ParallelSelector", BehaviorNodeType::Parallel) {};

    std::shared_ptr<BehaviorNode> ParallelSelector::Clone() const
    {
      return std::make_shared<ParallelSelector>(*this);
    }

    void ParallelSelector::OnBegin(BehaviorNodeInfo& info)
    {
      ParallelNode::OnBegin(childIndices_, dataArray_.Data(info.objectIndex_), false);
    }

    BehaviorState ParallelSelector::Execute(BehaviorNodeInfo& info)
    {
      ParallelNodeArrayElement& element = dataArray_.Data(info.objectIndex_);

      ParallelNode::Execute(childIndices_, element, info);

      bool oneSuccess = false;

      for (size_t i = 0; i < MAX_PARALLEL_NODE_CHILDREN; ++i)
      {
        int& nodeIndex = element.nodeIndices_[i];

        if (nodeIndex == PARALLEL_CHILD_SUCCESS)
        {
          oneSuccess = true;
        }
        else if (nodeIndex == PARALLEL_CHILD_FAILURE)
        {
          // do nothing
        }
        else
        {
          return BehaviorState::Running();
        }
      }

      if (oneSuccess)
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