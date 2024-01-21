/* ======================================================================== */
/*!
 * \file            BehaviorLoop.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef BehaviorLoop_BARRAGE_H
#define BehaviorLoop_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Behavior/BehaviorNode.hpp"

namespace Barrage
{
  namespace Behavior
  {
    class Loop : public BehaviorNode
    {
      public:
        Loop();

        std::shared_ptr<BehaviorNode> Clone() const override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorLoop_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////