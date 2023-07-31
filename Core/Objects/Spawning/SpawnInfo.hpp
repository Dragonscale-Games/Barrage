/* ======================================================================== */
/*!
 * \file            SpawnInfo.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Holds the information needed to spawn a new object.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnInfo_BARRAGE_H
#define SpawnInfo_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "SpawnRule.hpp"

#include <string>
#include <vector>

namespace Barrage
{
  class Pool;
  class ObjectArchetype;

  //!< Holds all information needed to spawn an object
  struct SpawnInfo
  {
    Pool* destinationPool_;           //!< destination pool pointer (should not be set manually)
    ObjectArchetype* spawnArchetype_; //!< spawn archetype pointer (should not be set manually)
    SpawnRuleList spawnRules_;        //!< Vector of spawn rule pointers (should not be set manually)

    std::vector<unsigned> sourceIndices_; //!< Indices of spawner objects (cleared after spawn)

    std::string destinationPoolName_;         //!< Name of the pool to spawn the object in
    std::string spawnArchetypeName_;          //!< Name of spawn archetype to use
    std::vector<std::string> spawnRuleNames_; //!< List of spawn rules to apply
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnInfo_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////