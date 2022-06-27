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
#include "Objects/SpawnFuncs/SpawnFuncManager.hpp"

namespace Barrage
{
  //!< Holds all information needed to spawn an object from another object
  struct SpawnType
  {
    std::vector<std::string> spawnFuncs_; //!< List of spawn functions to apply
    std::string poolName_;                //!< Name of pool the new object will spawn in
    std::string archetypeName_;           //!< Name of object archetype that will be cloned
    unsigned spawnNum_;                   //!< Number of objects to spawn this frame
    std::vector<unsigned> sourceIndices_; //!< Indices of spawner objects
  };
  
  //! Component that allows objects to spawn other objects
  class Spawner : public SharedComponent
  {
    public:
      std::vector<SpawnType> spawnTypes_; //!< List of the object types that will be spawned

      inline Spawner() : spawnTypes_() {}

      inline std::string GetClassName() override { return "Spawner"; }
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Spawner_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////