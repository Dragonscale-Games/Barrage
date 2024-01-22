/* ======================================================================== */
/*!
 * \file            BehaviorRepeat.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "BehaviorRepeat.hpp"

namespace Barrage
{
  namespace Behavior
  {
    Repeat::Repeat() : BehaviorNode("Repeat", BehaviorNodeType::Decorator) {};

    std::shared_ptr<BehaviorNode> Repeat::Clone() const
    {
      return std::make_shared<Repeat>(*this);
    }
  }
}