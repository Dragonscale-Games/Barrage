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

#include "Objects/Systems/System.hpp"

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
      static void SpawnObjects(Space& space, Pool& pool);
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // CreationSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////