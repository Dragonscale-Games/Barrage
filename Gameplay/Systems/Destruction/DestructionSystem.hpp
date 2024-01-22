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

#include "Objects/Systems/System.hpp"
#include "ComponentArrays/Destructible/DestructibleArray.hpp"

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
          The Behavior Tree component stores per-object data, so it
          needs to update this data on object destruction.

        \param pool
          The pool to update.
      */
      /**************************************************************/
      static void UpdateBehaviorPools(Space& space, Pool& pool);
      
      /**************************************************************/
      /*!
        \brief
          In spawn rules that store an array of per-spawner data,
          this function updates the elements of the array to match
          the positions of still-alive spawners when some spawners
          have been destroyed.

        \param pool
          The pool to update.
      */
      /**************************************************************/
      static void UpdateSpawnRules(Space& space, Pool& pool);
      
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
      static void DestroyObjects(Space& space, Pool& pool);

      /**************************************************************/
      /*!
        \brief
          Gets the index of the first dead object in the input array
          (or one past the end of the array if none exist).

        \param destructiblesArray
          The array to check for dead objects.

        \param numElements
          The number of elements to check.

        \return
          Returns the index of the first dead object in the input array
          (or one past the end of the array if none exist).
      */
      /**************************************************************/
      static unsigned GetFirstDeadObjectIndex(DestructibleArray& destructiblesArray, unsigned numElements);
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // DestructionSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////