/* ======================================================================== */
/*!
 * \file            Spawner.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Component that allows objects to spawn other objects.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Spawner_BARRAGE_H
#define Spawner_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/PoolComponent.hpp"

#include <vector>
#include <string>

namespace Barrage
{
  typedef std::vector<std::string> InitializerList;
  
  //!< Holds all information needed to spawn an object from another object
  struct SpawnType
  {
    InitializerList initializerNames_; //!< List of object initializer function names
    std::string poolName_;             //!< Name of pool the new object will spawn in
    std::string archetypeName_;        //!< Name of object archetype that will be cloned
    unsigned spawnNum_;                //!< Number of objects to spawn this frame
  };
  
  //! Component that allows objects to spawn other objects
  class Spawner : public PoolComponent
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Initializes spawner with an empty vector of SpawnTypes.
      */
      /**************************************************************/
      Spawner();

    public:
      std::vector<SpawnType> spawnTypes_; //!< List of the object types that will be spawned
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Spawner_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////