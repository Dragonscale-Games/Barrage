/* ======================================================================== */
/*!
 * \file            BehaviorLoopOnSuccess.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef BehaviorLoopOnSuccess_BARRAGE_H
#define BehaviorLoopOnSuccess_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Behavior/BehaviorNode.hpp"

namespace Barrage
{
  namespace Behavior
  {
    class LoopOnSuccess : public BehaviorNode
    {
      public:
        LoopOnSuccess();

        std::shared_ptr<BehaviorNode> Clone() const override;

        void OnBegin(BehaviorNodeInfo& info) override;

        BehaviorState Execute(BehaviorNodeInfo& info) override;

        void OnChildFinish(BehaviorNodeInfo& info, BehaviorState::State result, int childNodeIndex) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorLoopOnSuccess_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////