/* ======================================================================== */
/*!
 * \file            BehaviorAlwaysFail.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef BehaviorAlwaysFail_BARRAGE_H
#define BehaviorAlwaysFail_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Behavior/BehaviorNode.hpp"

namespace Barrage
{
  namespace Behavior
  {
    class AlwaysFail : public BehaviorNode
    {
      public:
        AlwaysFail();

        std::shared_ptr<BehaviorNode> Clone() const override;

        void OnBegin(BehaviorNodeInfo& info) override;

        BehaviorState Execute(BehaviorNodeInfo& info) override;

        void OnChildFinish(BehaviorNodeInfo& info, BehaviorState::State result, int childNodeIndex) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorAlwaysFail_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////