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
          Destroys all objects marked for destruction in a pool, 
          retaining the relative order between alive objects. Indices 
          for alive objects may be changed.

        \param pool
          The pool to update.
      */
      /**************************************************************/
      static void UpdateBasicDestructibles(Pool* pool);

      /**************************************************************/
      /*!
        \brief
          Algorithm that moves objects by copying each object one at
          a time, operating on all its components before moving onto 
          the next object.

        \param pool
          The pool to update.
      */
      /**************************************************************/
      static void PerObjectDestructionAlgorithm(Pool* pool);

      /**************************************************************/
      /*!
        \brief
          Algorithm that moves objects by focusing on one component
          array at a time, operating on a single component type for
          all objects before moving onto the next component type.

        \param pool
          The pool to update.
      */
      /**************************************************************/
      static void PerComponentDestructionAlgorithm(Pool* pool);

      /**************************************************************/
      /*!
        \brief
          Copies an object from one place in a pool to another place
          in the pool.

        \param pool
          The pool containing both objects.

        \param sourceIndex
          Index of the object that will be copied.

        \param recipientIndex
          Index of the object that will become a copy of the
          source object.
      */
      /**************************************************************/
      static void CopyObject(Pool* pool, unsigned sourceIndex, unsigned recipientIndex);
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // DestructionSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////