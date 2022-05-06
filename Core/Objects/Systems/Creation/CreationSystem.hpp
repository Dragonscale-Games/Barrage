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
#include "Objects/Archetypes/ArchetypeManager.hpp"
#include "Objects/SpawnFuncs/SpawnFuncManager.hpp"
#include "Objects/Pools/PoolManager.hpp"

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
          Clears the spawn type vectors. Hacky way to preserve
          capacity. Will be fixed in future iterations.
      */
      /**************************************************************/
      void Subscribe(Pool* pool) override;

      /**************************************************************/
      /*!
        \brief
          Creates all objects queued for spawning.
      */
      /**************************************************************/
      void Update() override;

      /**************************************************************/
      /*!
        \brief
          Sets the archetype manager the creation system will use
          to get object archetypes.

        \param archetypeManager
          The archetype manager that holds all object archetypes.
      */
      /**************************************************************/
      void SetArchetypeManager(ArchetypeManager& archetypeManager);

      /**************************************************************/
      /*!
        \brief
          Sets the initializer manager the creation system will use
          to look up initializers.

        \param initializerManager
          The initializer manager that holds all registered 
          initializers.
      */
      /**************************************************************/
      void SetSpawnFuncManager(SpawnFuncManager& spawnFuncManager);

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

        \param pool
          The object pool the new object will be created in.
      */
      /**************************************************************/
      void CreateObject(const ObjectArchetype& archetype, Pool* pool);

    private:
      /**************************************************************/
      /*!
        \brief
          Creates one or more new objects in an object pool using an
          object archetype as a template.

        \param archetype
          The archetype the new object(s) will be created from.

        \param pool
          The object pool the new object(s) will be created in.

        \param numNewObjects
          The number of objects to create.
      */
      /**************************************************************/
      void CreateObjects(const ObjectArchetype& archetype, Pool* pool, unsigned numNewObjects);

      /**************************************************************/
      /*!
        \brief
          Applies initialization functions to a number of objects
          in a destination pool, using information from another pool.

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
      void ApplySpawnFuncs(const std::vector<std::string>& spawnFuncs, Pool* initPool, Pool* destPool, unsigned startIndex, unsigned numObjects, const std::vector<unsigned>& sourceIndices);

      /**************************************************************/
      /*!
        \brief
          Update function for a single object pool.

        \param pool
          The pool to update.
      */
      /**************************************************************/
      void UpdateSpawners(Pool* pool);

    private:
      ArchetypeManager* archetypeManager_;  //!< Used to get object archetypes
      SpawnFuncManager* spawnFuncManager_;  //!< Used to look up spawn functions
      PoolManager* poolManager_;            //!< Used to get pools where objects will spawn
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // CreationSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////