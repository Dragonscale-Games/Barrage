/* ======================================================================== */
/*!
 * \file            Behavior.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here>

 */
 /* ======================================================================== */

#include "Behavior.hpp"

namespace Barrage
{
  template <>
  void ComponentT<BehaviorTree>::SetCapacity(unsigned capacity)
  {
    data_.SetCapacity(capacity);
  }

  template <>
  void ComponentT<BehaviorTree>::HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex)
  {
    data_.HandleDestructions(destructionArray, writeIndex, endIndex);
  }
}