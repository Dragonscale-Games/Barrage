/* ======================================================================== */
/*!
 * \file            Entry.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "stdafx.h"
#include "BehaviorTree.hpp"

#include <iostream>

namespace Barrage
{
  BehaviorNodeRecipe::BehaviorNodeRecipe(DeepPtr<BehaviorNode> node) : 
    node_(node), 
    children_()
  {
  }
  
  std::shared_ptr<BehaviorNodeRecipe> BehaviorNodeRecipe::Clone() const
  {
    return std::make_shared<BehaviorNodeRecipe>(*this);
  }

  BehaviorTree::BehaviorTree() :
    tree_(),
    recipe_(),
    nodeIndices_(),
    capacity_(1)
  {
  }

  void BehaviorTree::BuildTree()
  {
    if (!recipe_ || !recipe_->node_)
    {
      return;
    }

    tree_.clear();

    // node, parent index
    std::vector<std::pair<DeepPtr<BehaviorNodeRecipe>*, int>> nodeRecipes;

    // start with root node
    nodeRecipes.push_back(std::make_pair(&recipe_, BEHAVIOR_END));

    // nodeRecipes will grow as children are added later
    for (size_t i = 0; i < nodeRecipes.size(); ++i)
    {
      std::pair<DeepPtr<BehaviorNodeRecipe>*, int> recipePair = nodeRecipes.at(i);
      DeepPtr<BehaviorNodeRecipe>& nodeRecipe = *recipePair.first;
      int parentIndex = recipePair.second;
      int currentIndex = static_cast<int>(i);

      // set parent index of current node
      nodeRecipe->node_->SetParentIndex(parentIndex);

      // put current node in tree
      tree_.push_back(nodeRecipe->node_);
      
      // add this node as a child to its parent
      if (parentIndex >= 0)
      {
        tree_.at(parentIndex)->AddChildIndex(currentIndex);
      }

      // add recipes of children to queue for processing
      for (auto it = nodeRecipe->children_.begin(); it != nodeRecipe->children_.end(); ++it)
      {
        DeepPtr<BehaviorNodeRecipe>* childRecipePtr = &(*it);
        nodeRecipes.push_back(std::make_pair(childRecipePtr, currentIndex));
      }
    }

    for (auto it = tree_.begin(); it != tree_.end(); ++it)
    {
      DeepPtr<BehaviorNode>& behaviorNode = *it;

      if (behaviorNode->HasArray())
      {
        std::shared_ptr<BehaviorNodeWithArray> behaviorNodePtr = std::static_pointer_cast<BehaviorNodeWithArray>(behaviorNode.Get());

        behaviorNodePtr->SetCapacity(capacity_);
      }
    }
  }

  void BehaviorTree::Execute(Space& space, Pool& pool)
  {
    unsigned activeObjects = pool.ActiveObjectCount();

    for (unsigned i = 0; i < activeObjects; ++i)
    {
      BehaviorNodeInfo info(*this, space, pool, i);

      nodeIndices_.Data(i) = ExecuteNode(info, nodeIndices_.Data(i));
    }
  }

  int BehaviorTree::ExecuteNode(BehaviorNodeInfo& info, int nodeIndex)
  {
    if (nodeIndex <= BEHAVIOR_END || nodeIndex >= static_cast<int>(tree_.size()) || tree_.size() == 0)
    {
      return nodeIndex;
    }
    
    if (nodeIndex == BEHAVIOR_BEGIN)
    {
      nodeIndex = 0;
      tree_.at(nodeIndex)->OnBegin(info);
    }
    
    BehaviorState behaviorState = tree_.at(nodeIndex)->Execute(info);
    
    while (behaviorState.Get() != BehaviorState::State::Running)
    {
      switch (behaviorState.Get())
      {
        case BehaviorState::State::Transfer:
          nodeIndex = behaviorState.GetNextNodeIndex();
          tree_.at(nodeIndex)->OnBegin(info);
          break;

        case BehaviorState::State::Success:
          [[fallthrough]];
        case BehaviorState::State::Failure:
        {
          int childNodeIndex = nodeIndex;
          nodeIndex = tree_.at(nodeIndex)->GetParentIndex();

          if (nodeIndex <= BEHAVIOR_END)
          {
            return BEHAVIOR_END;
          }
          else if (tree_.at(nodeIndex)->GetType() == BehaviorNodeType::Parallel)
          {
            if (behaviorState.Get() == BehaviorState::State::Success)
            {
              return PARALLEL_CHILD_SUCCESS;
            }
            else
            {
              return PARALLEL_CHILD_FAILURE;
            }
          }

          tree_.at(nodeIndex)->OnChildFinish(info, behaviorState.Get(), childNodeIndex);
          break;
        }
      }
      
      behaviorState = tree_.at(nodeIndex)->Execute(info);
    }

    return nodeIndex;
  }

  void BehaviorTree::OnBeginNode(BehaviorNodeInfo& info, int nodeIndex)
  {
    if (nodeIndex < 0 || nodeIndex >= tree_.size())
    {
      return;
    }
    
    tree_.at(nodeIndex)->OnBegin(info);
  }

  void BehaviorTree::SetCapacity(unsigned capacity)
  {
    capacity_ = capacity;

    nodeIndices_.SetCapacity(capacity);

    for (unsigned i = 0; i < capacity; ++i)
    {
      nodeIndices_.Data(i) = BEHAVIOR_BEGIN;
    }
  }

  void BehaviorTree::HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex)
  {
    // TODO: optimize (store indices to array nodes)

    for (auto it = tree_.begin(); it != tree_.end(); ++it)
    {
      DeepPtr<BehaviorNode>& behaviorNode = *it;

      if (behaviorNode->HasArray())
      {
        std::shared_ptr<BehaviorNodeWithArray> behaviorNodePtr = std::static_pointer_cast<BehaviorNodeWithArray>(behaviorNode.Get());

        behaviorNodePtr->HandleDestructions(destructionArray, writeIndex, endIndex);
      }
    }

    unsigned numAliveObjects = nodeIndices_.HandleDestructions(destructionArray, writeIndex, endIndex);

    for (unsigned i = numAliveObjects; i < endIndex; ++i)
    {
      nodeIndices_.Data(i) = BEHAVIOR_BEGIN;
    }
  }

  void BehaviorTree::PrintNode(std::ostream& os, const std::string& name, unsigned level) const
  {
    for (unsigned i = 0; i < level; ++i)
    {
      os << "  ";
    }

    os << name << std::endl;
  }

  void BehaviorTree::PrintRecipeNode(std::ostream& os, const DeepPtr<BehaviorNodeRecipe>& recipeNode, unsigned level) const
  {
    PrintNode(os, recipeNode->node_->GetName(), level);

    for (auto it = recipeNode->children_.begin(); it != recipeNode->children_.end(); ++it)
    {
      PrintRecipeNode(os, *it, level + 1);
    }
  }

  void BehaviorTree::PrintTreeNode(std::ostream& os, const DeepPtr<BehaviorNode>& treeNode, unsigned level) const
  {
    PrintNode(os, treeNode->GetName(), level);

    for (auto it = treeNode->GetChildIndices().begin(); it != treeNode->GetChildIndices().end(); ++it)
    {
      PrintTreeNode(os, tree_.at(*it), level + 1);
    }
  }

  std::ostream& operator<<(std::ostream& os, const BehaviorTree& behaviorTree)
  {
    os << "Recipe:" << std::endl;
    os << "--------" << std::endl;

    if (behaviorTree.recipe_)
    {
      behaviorTree.PrintRecipeNode(os, behaviorTree.recipe_, 0);
    }

    os << std::endl;

    os << "Tree:" << std::endl;
    os << "------" << std::endl;

    if (!behaviorTree.tree_.empty())
    {
      behaviorTree.PrintTreeNode(os, behaviorTree.tree_.at(0), 0);
    }

    os << std::endl;

    return os;
  }
}