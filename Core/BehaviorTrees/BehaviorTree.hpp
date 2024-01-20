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

namespace Barrage
{
  class BehaviorTree
  {
    public:
      BehaviorTree();

      void SetCapacity(unsigned capacity);

      void HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex);

    public:
      BehaviorNodeList tree_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorTree_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////