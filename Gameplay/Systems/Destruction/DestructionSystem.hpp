/* ======================================================================== */
/*!
 * \file            DestructionSystem.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Handles destruction for all destructible objects. All destroyed objects
   are lazy deleted, then all remaining active objects are sorted to the
   front of the pool and the active object count is updated.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef DestructionSystem_BARRAGE_H
#define DestructionSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Systems/BaseSystem.hpp"

namespace Barrage
{
  //! Handles destruction for all destructible objects
  class DestructionSystem : public System
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Initializes system.
      */
      /**************************************************************/
      DestructionSystem();
      
      /**************************************************************/
      /*!
        \brief
          Destroys all objects marked for destruction.
      */
      /**************************************************************/
      void Update() override;

    private:
      /**************************************************************/
      /*!
        \brief
          Destroys all objects marked for destruction in a pool, 
          retaining the relative order between alive objects. Indices 
          for alive objects may be changed.

        \param pool
          The pool to update.
      */
      /**************************************************************/
      static void DestroyObjects(Pool* pool);
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // DestructionSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////