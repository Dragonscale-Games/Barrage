/* ======================================================================== */
/*!
 * \file            BehaviorAlwaysSucceed.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef BehaviorAlwaysSucceed_BARRAGE_H
#define BehaviorAlwaysSucceed_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Behavior/BehaviorNode.hpp"

namespace Barrage
{
  namespace Behavior
  {
    class AlwaysSucceed : public BehaviorNode
    {
      public:
        AlwaysSucceed();

        std::shared_ptr<BehaviorNode> Clone() const override;

        void OnBegin(BehaviorNodeInfo& info) override;

        BehaviorState Execute(BehaviorNodeInfo& info) override;

        void OnChildFinish(BehaviorNodeInfo& info, BehaviorState::State result, int childNodeIndex) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorAlwaysSucceed_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////