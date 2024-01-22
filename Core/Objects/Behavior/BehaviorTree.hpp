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
  struct BehaviorNodeRecipe;
  
  class BehaviorNodeRecipeDeepPtr
  {
    public:
      BehaviorNodeRecipeDeepPtr(std::nullptr_t nullPointer = nullptr);

      BehaviorNodeRecipeDeepPtr(std::shared_ptr<BehaviorNodeRecipe> ptr);

      BehaviorNodeRecipeDeepPtr(const BehaviorNodeRecipeDeepPtr& other);

      BehaviorNodeRecipeDeepPtr& operator=(const BehaviorNodeRecipeDeepPtr& other);

      BehaviorNodeRecipeDeepPtr(BehaviorNodeRecipeDeepPtr&& other) noexcept;

      BehaviorNodeRecipeDeepPtr& operator=(BehaviorNodeRecipeDeepPtr&& other) noexcept;

      BehaviorNodeRecipe* operator->() const;

      BehaviorNodeRecipe& operator*() const;

      operator bool() const noexcept;

      std::shared_ptr<BehaviorNodeRecipe> Get() const;

    private:
      std::shared_ptr<BehaviorNodeRecipe> ptr_;
  };
  
  struct BehaviorNodeRecipe
  {
    BehaviorNodeDeepPtr node_;
    std::vector<BehaviorNodeRecipeDeepPtr> children_;

    inline BehaviorNodeRecipe(BehaviorNodeDeepPtr node) : node_(node), children_() {}
  };
  
  class BehaviorTree
  {
    public:
      BehaviorTree();

      void BuildTree();

      void Execute(Space& space, Pool& pool);

      void SetCapacity(unsigned capacity);

      void HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex);

      void PrintNode(std::ostream& os, const std::string& name, unsigned level) const;

      void PrintRecipeNode(std::ostream& os, const BehaviorNodeRecipeDeepPtr& recipeNode, unsigned level) const;

      void PrintTreeNode(std::ostream& os, const BehaviorNodeDeepPtr& treeNode, unsigned level) const;

      friend std::ostream& operator<<(std::ostream& os, const BehaviorTree& behaviorTree);
    
    private:
      // returns index of currently active node
      int ExecuteObject(BehaviorNodeInfo& info, int nodeIndex);

    public:
      BehaviorNodeList tree_;
      BehaviorNodeRecipeDeepPtr recipe_;
      ComponentArrayT<int> nodeIndices_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorTree_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////