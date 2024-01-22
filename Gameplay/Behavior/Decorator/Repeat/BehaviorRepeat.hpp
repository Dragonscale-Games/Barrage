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
    class Repeat : public BehaviorNode
    {
      public:
        Repeat();

        std::shared_ptr<BehaviorNode> Clone() const override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorRepeat_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////