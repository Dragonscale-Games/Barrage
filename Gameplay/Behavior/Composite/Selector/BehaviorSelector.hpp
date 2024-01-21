/* ======================================================================== */
/*!
 * \file            BehaviorSelector.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef BehaviorSelector_BARRAGE_H
#define BehaviorSelector_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Behavior/BehaviorNode.hpp"

namespace Barrage
{
  namespace Behavior
  {
    class Selector : public BehaviorNode
    {
      public:
        Selector();

        std::shared_ptr<BehaviorNode> Clone() const override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorSelector_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////