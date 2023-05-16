/* ======================================================================== */
/*!
 * \file            Spawner.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 

 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Spawner_BARRAGE_H
#define Spawner_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "../BaseClasses/SharedComponent.hpp"
#include "Objects/Spawning/SpawnInfo.hpp"

#include <unordered_map>
#include <string>

namespace Barrage
{ 
  typedef unsigned SpawnTypeId;
  typedef std::unordered_map<SpawnTypeId, SpawnInfo> SpawnTypeMap;

  //! Component that allows objects to spawn other objects
  class Spawner
  {
    public:
      SpawnTypeMap spawnTypes_; //!< List of the object types that will be spawned

      inline Spawner() : spawnTypes_() {}
  };

  typedef SharedComponentT<Spawner> SharedSpawner;
}

////////////////////////////////////////////////////////////////////////////////
#endif // Spawner_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////