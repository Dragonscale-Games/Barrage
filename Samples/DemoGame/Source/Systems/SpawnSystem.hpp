/* ======================================================================== */
/*!
 * \file            SpawnSystem.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnSystem_BARRAGE_H
#define SpawnSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Objects/Systems/BaseSystem.hpp>

namespace Demo
{
	//! Tells bullets when to spawn
  class SpawnSystem : public Barrage::System
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Initializes system.
      */
      /**************************************************************/
      SpawnSystem();
      
      /**************************************************************/
      /*!
        \brief
          Queues objects for spawn.
      */
      /**************************************************************/
      void Update() override;

    private:
      /**************************************************************/
      /*!
        \brief
          Update function for a single object pool.

        \param pool
          The pool to update.
      */
      /**************************************************************/
      static void UpdateBulletSpawners(Barrage::Pool* pool);
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////