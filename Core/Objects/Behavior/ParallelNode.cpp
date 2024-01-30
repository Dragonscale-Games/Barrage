/* ======================================================================== */
/*!
 * \file            ParallelNode.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "ParallelNode.hpp"
#include "BehaviorTree.hpp"

namespace Barrage
{
  ParallelNodeArrayElement::ParallelNodeArrayElement() :
    nodeIndices_
    {
      PARALLEL_CHILD_SUCCESS,
      PARALLEL_CHILD_SUCCESS,
      PARALLEL_CHILD_SUCCESS,
      PARALLEL_CHILD_SUCCESS
    }
  {
  }

  void ParallelNode::OnBegin(
    const std::vector<int>& childIndices, 
    ParallelNodeArrayElement& element, 
    bool defaultSuccess
  )
  {
    size_t numChildren = childIndices.size();

    if (numChildren > MAX_PARALLEL_NODE_CHILDREN)
    {
      numChildren = MAX_PARALLEL_NODE_CHILDREN;
    }

    for (size_t i = 0; i < numChildren; ++i)
    {
      element.nodeIndices_[i] = PARALLEL_CHILD_BEGIN;
    }

    for (size_t i = numChildren; i < MAX_PARALLEL_NODE_CHILDREN; ++i)
    {
      element.nodeIndices_[i] = defaultSuccess ? PARALLEL_CHILD_SUCCESS : PARALLEL_CHILD_FAILURE;
    }
  }

  void ParallelNode::Execute(
    const std::vector<int>& childIndices, 
    ParallelNodeArrayElement& element, 
    BehaviorNodeInfo& info
  )
  {
    for (size_t i = 0; i < MAX_PARALLEL_NODE_CHILDREN; ++i)
    {
      int& nodeIndex = element.nodeIndices_[i];

      if (nodeIndex == PARALLEL_CHILD_BEGIN)
      {
        nodeIndex = childIndices[i];
        info.tree_.OnBeginNode(info, nodeIndex);
      }

      nodeIndex = info.tree_.ExecuteNode(info, nodeIndex);
    }
  }
}