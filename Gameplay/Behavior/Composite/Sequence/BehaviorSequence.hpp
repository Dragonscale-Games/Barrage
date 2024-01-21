/* ======================================================================== */
/*!
 * \file            BehaviorSequence.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef BehaviorSequence_BARRAGE_H
#define BehaviorSequence_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Behavior/BehaviorNode.hpp"

namespace Barrage
{
  namespace Behavior
  {
    class Sequence : public BehaviorNode
    {
      public:
        Sequence();

        std::shared_ptr<BehaviorNode> Clone() const override;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorSequence_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////