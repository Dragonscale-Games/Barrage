/* ======================================================================== */
/*!
 * \file            BehaviorTree.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef BehaviorTree_BARRAGE_H
#define BehaviorTree_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "BehaviorNode.hpp"
#include "Objects/Components/ComponentArray.hpp"

#include <iostream>

namespace Barrage
{
  struct BehaviorNodeRecipe
  {
    DeepPtr<BehaviorNode> node_;
    std::vector<DeepPtr<BehaviorNodeRecipe>> children_;

    BehaviorNodeRecipe(DeepPtr<BehaviorNode> node);

    std::shared_ptr<BehaviorNodeRecipe> Clone() const;
  };
  
  class BehaviorTree
  {
    public:
      BehaviorTree();

      void BuildTree();

      void Execute(Space& space, Pool& pool);

      int ExecuteNode(BehaviorNodeInfo& info, int nodeIndex);

      void OnBeginNode(BehaviorNodeInfo& info, int nodeIndex);

      void SetCapacity(unsigned capacity);

      void HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex);

      void PrintNode(std::ostream& os, const std::string& name, unsigned level) const;

      void PrintRecipeNode(std::ostream& os, const DeepPtr<BehaviorNodeRecipe>& recipeNode, unsigned level) const;

      void PrintTreeNode(std::ostream& os, const DeepPtr<BehaviorNode>& treeNode, unsigned level) const;

      friend std::ostream& operator<<(std::ostream& os, const BehaviorTree& behaviorTree);

    public:
      BehaviorNodeList tree_;
      DeepPtr<BehaviorNodeRecipe> recipe_;
      ComponentArrayT<int> nodeIndices_;
      unsigned capacity_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorTree_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////