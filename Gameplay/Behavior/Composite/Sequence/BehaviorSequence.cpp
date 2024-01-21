/* ======================================================================== */
/*!
 * \file            BehaviorSequence.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "BehaviorSequence.hpp"

namespace Barrage
{
  namespace Behavior
  {
    Sequence::Sequence() : BehaviorNode("Sequence", BehaviorNodeType::Composite) {};

    std::shared_ptr<BehaviorNode> Sequence::Clone() const
    {
      return std::make_shared<Sequence>(*this);
    }
  }
}