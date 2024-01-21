/* ======================================================================== */
/*!
 * \file            BehaviorSelector.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "BehaviorSelector.hpp"

namespace Barrage
{
  namespace Behavior
  {
    Selector::Selector() : BehaviorNode("Selector", BehaviorNodeType::Decorator) {};

    std::shared_ptr<BehaviorNode> Selector::Clone() const
    {
      return std::make_shared<Selector>(*this);
    }
  }
}