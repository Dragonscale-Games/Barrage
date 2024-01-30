/* ======================================================================== */
/*!
 * \file            BehaviorParallelSequence.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef BehaviorParallelSequence_BARRAGE_H
#define BehaviorParallelSequence_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Behavior/BehaviorNode.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  namespace Behavior
  {
    class ParallelSequence : public BehaviorNodeTA<Dummy, ParallelNodeArrayElement>
    {
      public:
        ParallelSequence();

        std::shared_ptr<BehaviorNode> Clone() const override;

        void OnBegin(BehaviorNodeInfo& info) override;

        BehaviorState Execute(BehaviorNodeInfo& info) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorParallelSequence_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////