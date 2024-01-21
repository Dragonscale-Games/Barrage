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
      unsigned ticks_;

      WaitData();
    };
    
    class Wait : public BehaviorNodeT<WaitData>
    {
      public:
        Wait();

        std::shared_ptr<BehaviorNode> Clone() const override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorWait_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////