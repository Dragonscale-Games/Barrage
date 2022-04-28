/* ======================================================================== */
/*!
 * \file            BaseSystem.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base object system class that all object systems should inherit from.

   An object system is a collection of related functions that perform operations
   on game object components. For instance, a movement system might contain all
   functions that change an object's position component.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef BaseSystem_BARRAGE_H
#define BaseSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "../Pools/Pool.hpp"

#include <map>

namespace Barrage
{
  typedef std::multimap<unsigned, Pool*> OrderedPoolMap;

  //! Base object system class that all object systems should inherit from
  class System
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Initializes system.
      */
      /**************************************************************/
      System();

      /**************************************************************/
      /*!
        \brief
          Base class requires virtual destructor.
      */
      /**************************************************************/
      virtual ~System() = default;

      /**************************************************************/
      /*!
        \brief
          Determines if an object pool has the set of components the
          system cares about and, if so, subscribes it to the system.

          Virtual so the user may define their own key assignment
          scheme. For instance, in a graphics system, the user may
          wish to assign keys based on the layer an object pool draws
          in.
      */
      /**************************************************************/
      virtual void Subscribe(Pool* pool);

      /**************************************************************/
      /*!
        \brief
          Determines if an object pool is subscribed to the system
          and, if so, unsubscribes it from the system.
      */
      /**************************************************************/
      void Unsubscribe(Pool* pool);

      /**************************************************************/
      /*!
        \brief
          Carries out system functions on all object pools subscribed
          to the system. The default version simply loops through
          every object pool and calls UpdatePool on it, but the user
          may specify their own Update function.
      */
      /**************************************************************/
      virtual void Update();

    protected:
      /**************************************************************/
      /*!
        \brief
          Update function for a single object pool.

        \param pool
          The pool to update.
      */
      /**************************************************************/
      virtual void UpdatePool(Pool* pool);

      /**************************************************************/
      /*!
        \brief
          Determines if an object pool has the set of components the
          system cares about (using the system component list).
      */
      /**************************************************************/
      bool PoolMatchesSystem(Pool* pool);

    protected:
      ComponentList systemComponents_; //!< Holds the names of all the components the system cares about
      OrderedPoolMap pools_;           //!< Holds all subscribed pools in the order they are to be updated (based on key given in Subscribe)
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // BaseSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////