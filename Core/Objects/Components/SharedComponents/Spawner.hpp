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

#include <unordered_map>
#include <string>

namespace Barrage
{ 
  //!< Holds all information needed to spawn an object from another object
  struct SpawnType
  {
    std::string archetypeName_;           //!< Name of object archetype that will be spawned
    std::string destinationPoolName_;     //!< Name of pool the new object will spawn in
    unsigned destinationPoolCapacity_;    //!< Max number of objects the destination pool can hold
    std::vector<std::string> spawnFuncs_; //!< List of spawn functions to apply
    std::vector<unsigned> sourceIndices_; //!< Indices of spawner objects
  };
  
  typedef std::unordered_map<std::string, SpawnType> SpawnTypeMap;

  //! Component that allows objects to spawn other objects
  class Spawner : public SharedComponent
  {
    public:
      SpawnTypeMap spawnTypes_; //!< List of the object types that will be spawned

      inline Spawner() : spawnTypes_() {}

      inline std::string GetClassName() override { return "Spawner"; }
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Spawner_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////