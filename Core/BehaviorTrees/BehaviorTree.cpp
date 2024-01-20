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
    tree_()
  {
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
}