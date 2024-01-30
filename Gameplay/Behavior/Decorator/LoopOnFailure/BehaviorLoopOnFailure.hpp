/* ======================================================================== */
/*!
 * \file            BehaviorLoopOnFailure.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef BehaviorLoopOnFailure_BARRAGE_H
#define BehaviorLoopOnFailure_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Behavior/BehaviorNode.hpp"

namespace Barrage
{
  namespace Behavior
  {
    class LoopOnFailure : public BehaviorNode
    {
      public:
        LoopOnFailure();

        std::shared_ptr<BehaviorNode> Clone() const override;

        void OnBegin(BehaviorNodeInfo& info) override;

        BehaviorState Execute(BehaviorNodeInfo& info) override;

        void OnChildFinish(BehaviorNodeInfo& info, BehaviorState::State result, int childNodeIndex) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorLoopOnFailure_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////