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

namespace Barrage
{
  BehaviorTree::BehaviorTree() :
    tree_(),
    recipe_()
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
    std::vector<std::pair<BehaviorNodeRecipeDeepPtr*, int>> nodeRecipes;

    // start with root node
    nodeRecipes.push_back(std::make_pair(&recipe_, BEHAVIOR_END));

    // nodeRecipes will grow as children are added later
    for (size_t i = 0; i < nodeRecipes.size(); ++i)
    {
      std::pair<BehaviorNodeRecipeDeepPtr*, int> recipePair = nodeRecipes.at(i);
      BehaviorNodeRecipeDeepPtr& nodeRecipe = *recipePair.first;
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
        BehaviorNodeRecipeDeepPtr* childRecipePtr = &(*it);
        nodeRecipes.push_back(std::make_pair(childRecipePtr, currentIndex));
      }
    }
  }

  int BehaviorTree::Execute(BehaviorNodeInfo& info, int nodeIndex)
  {
    if (nodeIndex <= BEHAVIOR_END || nodeIndex >= tree_.size() || tree_.size() == 0)
    {
      return BEHAVIOR_END;
    }
    
    if (nodeIndex == BEHAVIOR_BEGIN)
    {
      nodeIndex = 0;
      tree_.at(nodeIndex)->OnBegin(info);
    }
    
    BehaviorState behaviorState = tree_.at(nodeIndex)->Execute(info);
    
    while (behaviorState.GetState() != BehaviorState::State::Running)
    {
      switch (behaviorState.GetState())
      {
        case BehaviorState::State::Transfer:
          nodeIndex = behaviorState.GetNextNodeIndex();
          tree_.at(nodeIndex)->OnBegin(info);
          break;

        case BehaviorState::State::Success:
          [[fallthrough]];
        case BehaviorState::State::Failure:
        {
          int childIndex = nodeIndex;
          nodeIndex = tree_.at(nodeIndex)->GetParentIndex();

          if (nodeIndex == BEHAVIOR_END)
          {
            return BEHAVIOR_END;
          }

          tree_.at(nodeIndex)->OnChildFinish(info, behaviorState.GetState(), childIndex);
          break;
        }
      }
      
      behaviorState = tree_.at(nodeIndex)->Execute(info);
    }

    return nodeIndex;
  }

  void BehaviorTree::SetCapacity(unsigned capacity)
  {
    // TODO: optimize (store indices to array nodes)

    for (auto it = tree_.begin(); it != tree_.end(); ++it)
    {
      BehaviorNodeDeepPtr& behaviorNode = *it;

      if (behaviorNode->HasArray())
      {
        std::shared_ptr<BehaviorNodeWithArray> behaviorNodePtr = std::static_pointer_cast<BehaviorNodeWithArray>(behaviorNode.Get());

        behaviorNodePtr->SetCapacity(capacity);
      }
    }
  }

  void BehaviorTree::HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex)
  {
    // TODO: optimize (store indices to array nodes)

    for (auto it = tree_.begin(); it != tree_.end(); ++it)
    {
      BehaviorNodeDeepPtr& behaviorNode = *it;

      if (behaviorNode->HasArray())
      {
        std::shared_ptr<BehaviorNodeWithArray> behaviorNodePtr = std::static_pointer_cast<BehaviorNodeWithArray>(behaviorNode.Get());

        behaviorNodePtr->HandleDestructions(destructionArray, writeIndex, endIndex);
      }
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

  void BehaviorTree::PrintRecipeNode(std::ostream& os, const BehaviorNodeRecipeDeepPtr& recipeNode, unsigned level) const
  {
    PrintNode(os, recipeNode->node_->GetName(), level);

    for (auto it = recipeNode->children_.begin(); it != recipeNode->children_.end(); ++it)
    {
      PrintRecipeNode(os, *it, level + 1);
    }
  }

  void BehaviorTree::PrintTreeNode(std::ostream& os, const BehaviorNodeDeepPtr& treeNode, unsigned level) const
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
    
    os << "Tree:" << std::endl;
    os << "------" << std::endl;

    if (!behaviorTree.tree_.empty())
    {
      behaviorTree.PrintTreeNode(os, behaviorTree.tree_.at(0), 0);
    }
    
    return os;
  }

  BehaviorNodeRecipeDeepPtr::BehaviorNodeRecipeDeepPtr(std::nullptr_t) :
    ptr_(nullptr)
  {
  }

  BehaviorNodeRecipeDeepPtr::BehaviorNodeRecipeDeepPtr(std::shared_ptr<BehaviorNodeRecipe> ptr) :
    ptr_(ptr)
  {
  }

  BehaviorNodeRecipeDeepPtr::BehaviorNodeRecipeDeepPtr(const BehaviorNodeRecipeDeepPtr& other) :
    ptr_(other ? std::make_shared<BehaviorNodeRecipe>(*other.Get()) : nullptr)
  {
  }

  BehaviorNodeRecipeDeepPtr& BehaviorNodeRecipeDeepPtr::operator=(const BehaviorNodeRecipeDeepPtr& other)
  {
    if (this != &other) // Prevent self-assignment
    {
      ptr_ = other ? std::make_shared<BehaviorNodeRecipe>(*other.Get()) : nullptr;
    }

    return *this;
  }

  BehaviorNodeRecipeDeepPtr::BehaviorNodeRecipeDeepPtr(BehaviorNodeRecipeDeepPtr&& other) noexcept :
    ptr_(std::move(other.ptr_))
  {
  }

  BehaviorNodeRecipeDeepPtr& BehaviorNodeRecipeDeepPtr::operator=(BehaviorNodeRecipeDeepPtr&& other) noexcept
  {
    if (this != &other) // Prevent self-assignment
    {
      ptr_ = std::move(other.ptr_);
    }

    return *this;
  }

  BehaviorNodeRecipe* BehaviorNodeRecipeDeepPtr::operator->() const
  {
    return ptr_.operator->();
  }

  BehaviorNodeRecipe& BehaviorNodeRecipeDeepPtr::operator*() const
  {
    return *ptr_;
  }

  BehaviorNodeRecipeDeepPtr::operator bool() const noexcept
  {
    return static_cast<bool>(ptr_);
  }

  std::shared_ptr<BehaviorNodeRecipe> BehaviorNodeRecipeDeepPtr::Get() const
  {
    return ptr_;
  }
}