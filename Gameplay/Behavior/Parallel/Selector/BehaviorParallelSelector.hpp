/* ======================================================================== */
/*!
 * \file            BehaviorParallelSelector.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef BehaviorParallelSelector_BARRAGE_H
#define BehaviorParallelSelector_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Behavior/BehaviorNode.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  namespace Behavior
  {
    class ParallelSelector : public BehaviorNodeTA<Dummy, ParallelNodeArrayElement>
    {
      public:
        ParallelSelector();

        std::shared_ptr<BehaviorNode> Clone() const override;

        void OnBegin(BehaviorNodeInfo& info) override;

        BehaviorState Execute(BehaviorNodeInfo& info) override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorParallelSelector_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////