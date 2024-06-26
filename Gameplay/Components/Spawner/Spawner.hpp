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

#include "Objects/Components/Component.hpp"
#include "Objects/Spawning/SpawnType.hpp"

#include <unordered_map>
#include <string>
#include <vector>

namespace Barrage
{ 
  //!< Contains the info needed to spawn objects automatically
  struct AutomaticSpawn
  {
    std::string spawnType_;   //!< The spawn type to use
    unsigned ticksPerSpawn_;  //!< Amount of time between object spawns (zero means the object is only spawned once)
    unsigned delay_;          //!< the spawn timer tick when the automatic spawning begins

    AutomaticSpawn();
  };

  //!< Contains the info needed to intelligently spawn objects
  struct SpawnPattern
  {
    std::vector<AutomaticSpawn> automaticSpawns_; //!< Spawns that repeat automatically

    SpawnPattern();
  };

  typedef std::map<std::string, SpawnPattern> PatternMap;

  //! Component that allows objects to spawn other objects
  class Spawner
  {
    public:
      std::string currentPattern_;            //!< The current pattern being used by the spawner
      PatternMap patterns_;                   //!< The patterns available to use
      SpawnTypeMap spawnTypes_;               //!< The spawn types available to use
      ComponentArrayT<unsigned> spawnTimers_; //!< Per-object spawn timers

      Spawner();

      static void Reflect();
  };

  typedef ComponentT<Spawner> SpawnerComponent;

  template <>
  void ComponentT<Spawner>::SetCapacity(unsigned capacity);

  template <>
  void ComponentT<Spawner>::HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex);
}

////////////////////////////////////////////////////////////////////////////////
#endif // Spawner_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////