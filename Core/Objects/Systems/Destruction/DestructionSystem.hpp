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

#include "../BaseSystem.hpp"

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
          Frees the handles of dead objects.

        \param pool
          The pool to update.
      */
      /**************************************************************/
      static void UpdateDeadHandles(Pool* pool);

      /**************************************************************/
      /*!
        \brief
          Updates the handles of alive objects to reflect their
          new locations.

        \param pool
          The pool to update.
      */
      /**************************************************************/
      static void UpdateAliveHandles(Pool* pool);

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