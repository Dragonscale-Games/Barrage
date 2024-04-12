/* ======================================================================== */
/*!
 * \file            SpawnLayer.hpp
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

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnLayer_BARRAGE_H
#define SpawnLayer_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "SpawnRule.hpp"
#include "Objects/Components/ComponentArray.hpp"

namespace Barrage
{
  class SpawnLayer
  {
    public:
      SpawnLayer();

      void SetCapacity(unsigned capacity);

      void HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex);

    public:
      unsigned baseNumGroups_;
      ComponentArrayT<GroupInfo> groupInfoArray_;
      SpawnRuleList valueRules_;
      SpawnRuleList countRules_;

      friend class SpawnType;
      friend class Pool;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnType_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////