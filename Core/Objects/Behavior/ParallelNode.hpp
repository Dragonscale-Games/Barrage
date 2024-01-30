/* ======================================================================== */
/*!
 * \file            ParallelNode.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef ParallelNode_BARRAGE_H
#define ParallelNode_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <vector>

namespace Barrage
{
  class BehaviorTree;
  struct BehaviorNodeInfo;

  constexpr int PARALLEL_CHILD_BEGIN = -3;
  constexpr int PARALLEL_CHILD_SUCCESS = -4;
  constexpr int PARALLEL_CHILD_FAILURE = -5;

  constexpr size_t MAX_PARALLEL_NODE_CHILDREN = 4;

  struct ParallelNodeArrayElement
  {
    int nodeIndices_[4];

    ParallelNodeArrayElement();
  };

  namespace ParallelNode
  {
    void OnBegin(
      const std::vector<int>& childIndices, 
      ParallelNodeArrayElement& element,
      bool defaultSuccess = true);

    void Execute(
      const std::vector<int>& childIndices, 
      ParallelNodeArrayElement& element,  
      BehaviorNodeInfo& info);
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // ParallelNode_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////