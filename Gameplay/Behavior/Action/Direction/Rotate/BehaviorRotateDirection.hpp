/* ======================================================================== */
/*!
 * \file            BehaviorRotateDirection.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef BehaviorRotateDirection_BARRAGE_H
#define BehaviorRotateDirection_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Behavior/BehaviorNode.hpp"

namespace Barrage
{
  namespace Behavior
  {
    struct RotateDirectionData
    {
      Radian angle_;

      inline RotateDirectionData() : angle_(0.0f) {};
    };

    class RotateDirection : public BehaviorNodeT<RotateDirectionData>
    {
      public:
        RotateDirection();

        std::shared_ptr<BehaviorNode> Clone() const override;

        BehaviorState Execute(BehaviorNodeInfo& info) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorRotateDirection_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////