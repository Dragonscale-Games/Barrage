/* ======================================================================== */
/*!
 * \file            BehaviorLoop.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "BehaviorLoop.hpp"

namespace Barrage
{
  namespace Behavior
  {
    Loop::Loop() : BehaviorNode("Loop", BehaviorNodeType::Decorator) {};

    std::shared_ptr<BehaviorNode> Loop::Clone() const
    {
      return std::make_shared<Loop>(*this);
    }
  }
}