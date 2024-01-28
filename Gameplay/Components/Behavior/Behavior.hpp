/* ======================================================================== */
/*!
 * \file            Behavior.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here>

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Behavior_BARRAGE_H
#define Behavior_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/Component.hpp"
#include "Objects/Behavior/BehaviorTree.hpp"

namespace Barrage
{
  typedef Barrage::ComponentT<BehaviorTree> BehaviorTreeComponent;

  template <>
  void ComponentT<BehaviorTree>::SetCapacity(unsigned capacity);

  template <>
  void ComponentT<BehaviorTree>::HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex);
}

////////////////////////////////////////////////////////////////////////////////
#endif // Behavior_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////