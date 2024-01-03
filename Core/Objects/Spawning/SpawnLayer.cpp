/* ======================================================================== */
/*!
 * \file            SpawnLayer.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A spawn layer is a collection of spawn rules plus information about how
   to apply them to sets of objects. For instance, a spawn rule might apply a
   unique value to each individual object in a spawn, or it might apply a unique
   value to every set of X objects.
*/
/* ======================================================================== */

#include "SpawnLayer.hpp"

namespace Barrage
{
  SpawnLayer::SpawnLayer() :
    baseNumGroups_(1),
    groupInfoArray_(),
    sizeRules_(),
    valueRules_()
  {
  }

  void SpawnLayer::SetCapacity(unsigned capacity)
  {
    groupInfoArray_.SetCapacity(capacity);

    for (unsigned i = 0; i < capacity; ++i)
    {
      groupInfoArray_.Data(i) = GroupInfo(baseNumGroups_);
    }

    sizeRules_.SetCapacity(capacity);
    valueRules_.SetCapacity(capacity);
  }

  void SpawnLayer::HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex)
  {
    unsigned numAliveObjects = groupInfoArray_.HandleDestructions(destructionArray, writeIndex, endIndex);

    for (unsigned i = numAliveObjects; i < endIndex; ++i)
    {
      groupInfoArray_.Data(i) = GroupInfo(baseNumGroups_);
    }
    
    sizeRules_.HandleDestructions(destructionArray, writeIndex, endIndex);
    valueRules_.HandleDestructions(destructionArray, writeIndex, endIndex);
  }
}