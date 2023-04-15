/* ======================================================================== */
/*!
 * \file            CreationSystem.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Handles object creation both directly (through an object creation function)
   and indirectly (through updating object spawners).
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef CreationSystem_BARRAGE_H
#define CreationSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Systems/BaseSystem.hpp"
#include "Objects/Archetypes/ObjectArchetype/ObjectArchetype.hpp"
#include "Objects/Spawning/SpawnFunctionManager.hpp"
#include "Objects/Pools/PoolManager.hpp"
#include "Objects/Components/SharedComponents/Spawner.hpp"
#include "Objects/Spawning/SpawnInfo.hpp"

namespace Barrage
{
  //! Handles object creation
  class CreationSystem : public System
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Initializes system.
      */
      /**************************************************************/
      CreationSystem();

      /**************************************************************/
      /*!
        \brief
          Spawns all objects queued for spawning.
      */
      /**************************************************************/
      void Update() override;

      /**************************************************************/
      /*!
        \brief
          Sets the pool manager the creation system will use to spawn
          objects into.

        \param poolManager
          The pool manager that holds all active object pools.
      */
      /**************************************************************/
      void SetPoolManager(PoolManager& poolManager);

      /**************************************************************/
      /*!
        \brief
          Creates a new object in an object pool using an object
          archetype. 

        \param archetype
          The archetype the new object will be created from.

        \param destinationPool
          The object pool the new object will be created in.
      */
      /**************************************************************/
      void CreateObject(const ObjectArchetype& archetype, Pool* destinationPool);

      /**************************************************************/
      /*!
        \brief
          Queues objects for spawn using information from the input
          SpawnType. The size of the sourceIndices vector is used to 
          determine how many objects to spawn. This function always 
          sets the size of the sourceIndices vector to zero. 

        \param sourcePool
          The pool the spawn command is coming from.

        \param spawnType
          Holds information about how and where to spawn the objects.
      */
      /**************************************************************/
      void QueueSpawns(Pool* sourcePool, SpawnInfo& spawnType);

    private:
      /**************************************************************/
      /*!
        \brief
          Creates one or more new objects in an object pool using an
          object archetype as a template.

        \param archetype
          The archetype the new object(s) will be created from.

        \param destinationPool
          The object pool the new object(s) will be created in.

        \param numNewObjects
          The number of objects to attempt to create.

        \param queueObjects
          If true, the objects will not spawn until the creation
          system updates. 
      */
      /**************************************************************/
      void CreateObjects(const ObjectArchetype& archetype, Pool* destinationPool, unsigned numNewObjects, bool queueObjects);

      /**************************************************************/
      /*!
        \brief
          Applies spawn functions to objects in a destination pool, 
          using information from the source pool.

        \param initializers
          The list of initializers to apply.

        \param initPool
          The pool whose information will be used to initialize 
          objects in the destination pool.

        \param destPool
          The pool whose objects are being initialized.

        \param startIndex
          The index of the first object to initialize in the 
          destination pool.

        \param numObjects
          The number of objects to initialize.
      */
      /**************************************************************/
      void ApplySpawnFuncs(const std::vector<std::string>& spawnFuncs, Pool* sourcePool, Pool* destinationPool, unsigned startIndex, unsigned numObjects, const std::vector<unsigned>& sourceIndices);

      /**************************************************************/
      /*!
        \brief
          Spawns all objects waiting to be spawned in a given pool.

        \param pool
          The pool to update.
      */
      /**************************************************************/
      static void SpawnObjects(Pool* pool);

      /**************************************************************/
      /*!
        \brief
          Creates a handle for each object that needs one.

        \param pool
          The pool to update.
      */
      /**************************************************************/
      static void AssignHandles(Pool* pool);

    private:
      PoolManager* poolManager_;                    //!< Used to get pools where objects will spawn
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // CreationSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////