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
          Subscribes pools to the spawn system and verifies spawns
          are legal.
      */
      /**************************************************************/
      void Subscribe(Pool* pool) override;

      /**************************************************************/
      /*!
        \brief
          Queues objects for spawn.
      */
      /**************************************************************/
      void Update() override;

    private:
      static void Spawn(Pool* pool);

      static void UpdateSpawnTimers(Pool* pool);

      void LinkAndValidateSpawns(Pool* pool);
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////