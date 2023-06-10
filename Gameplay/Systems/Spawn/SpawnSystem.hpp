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

namespace Barrage
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
      static void SpawnBullets(Barrage::Pool* spawnerPool, Barrage::Pool* bulletPool);
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////