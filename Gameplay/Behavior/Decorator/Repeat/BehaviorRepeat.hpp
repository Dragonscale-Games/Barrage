/* ======================================================================== */
/*!
 * \file            BehaviorRepeat.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef BehaviorRepeat_BARRAGE_H
#define BehaviorRepeat_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Behavior/BehaviorNode.hpp"

namespace Barrage
{
  namespace Behavior
  {
    struct RepeatData
    {
      unsigned numIterations_;

      RepeatData();
    };

    struct RepeatArrayElement
    {
      unsigned currentIterations_;

      RepeatArrayElement();
    };
    
    class Repeat : public BehaviorNodeTA<RepeatData, RepeatArrayElement>
    {
      public:
        Repeat();

        std::shared_ptr<BehaviorNode> Clone() const override;

        void OnBegin(BehaviorNodeInfo& info) override;

        BehaviorState Execute(BehaviorNodeInfo& info) override;

        void OnChildFinish(BehaviorNodeInfo& info, BehaviorState::State result, int childNodeIndex) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorRepeat_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////