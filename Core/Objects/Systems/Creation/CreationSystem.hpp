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
#include "Objects/Components/Components/Spawner.hpp"
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

    private:
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
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // CreationSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////