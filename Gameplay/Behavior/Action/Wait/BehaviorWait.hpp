/* ======================================================================== */
/*!
 * \file            BehaviorWait.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef BehaviorWait_BARRAGE_H
#define BehaviorWait_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Behavior/BehaviorNode.hpp"

namespace Barrage
{
  namespace Behavior
  {
    struct WaitData
    {
      unsigned numTicks_;

      WaitData();
    };
    
    struct WaitArrayElement
    {
      unsigned elapsedTicks_;

      WaitArrayElement();
    };

    class Wait : public BehaviorNodeTA<WaitData, WaitArrayElement>
    {
      public:
        Wait();

        std::shared_ptr<BehaviorNode> Clone() const override;

        BehaviorState Execute(BehaviorNodeInfo& info) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorWait_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////