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

#include "Objects/Components/BaseClasses/Component.hpp"
#include "Objects/Spawning/SpawnInfo.hpp"

#include <unordered_map>
#include <string>
#include <vector>

namespace Barrage
{ 
  typedef unsigned Tick;

  //!< Holds names of spawn types
  struct SpawnTypeList
  {
    std::vector<std::string> spawnTypes_;
  };

  typedef std::unordered_map<Tick, SpawnTypeList> SpawnSequence;

  //!< Contains the info needed to spawn objects at a regular rate
  struct AutomaticSpawn
  {
    std::string spawnType_;   //!< The spawn type to use
    unsigned ticksPerSpawn_;  //!< Amount of time between object spawns 
    unsigned numberPerBurst_; //!< Number of spawns per burst
    unsigned delay_;          //!< the spawn timer tick when the automatic spawning begins

    inline AutomaticSpawn() :
      spawnType_(),
      ticksPerSpawn_(120),
      numberPerBurst_(1),
      delay_(0)
    {
    }
  };

  //!< Contains the info needed to intelligently spawn objects
  struct SpawnPattern
  {
    SpawnSequence spawnSequence_;                 //!< Spawns that happen on a specific spawn timer tick
    std::vector<AutomaticSpawn> automaticSpawns_; //!< Spawns that repeat automatically
  };

  typedef std::unordered_map<std::string, SpawnPattern> PatternMap;
  typedef std::unordered_map<std::string, SpawnInfo> SpawnTypeMap;

  //! Component that allows objects to spawn other objects
  class Spawner
  {
    public:
      std::string currentPattern_; //!< The current pattern being used by the spawner
      PatternMap patterns_;        //!< The patterns available to use
      SpawnTypeMap spawnTypes_;    //!< The object types available for spawning

      inline Spawner() : spawnTypes_() {}
  };

  typedef ComponentT<Spawner> SpawnerComponent;
}

////////////////////////////////////////////////////////////////////////////////
#endif // Spawner_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////