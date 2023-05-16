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

#include <string>
#include <vector>

namespace Barrage
{
  //!< Holds all information needed to spawn an object
  struct SpawnInfo
  {
    std::string archetypeName_;                //!< Name of object archetype that will be spawned
    std::vector<std::string> spawnFunctions_;  //!< List of spawn functions to apply
    std::vector<unsigned> sourceIndices_;      //!< Indices of spawner objects (cleared after spawn)
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnInfo_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////