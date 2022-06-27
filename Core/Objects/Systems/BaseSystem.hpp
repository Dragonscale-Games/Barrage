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
#include "../Pools/PoolType.hpp"
#include "Objects/Components/EngineComponents.hpp"
#include <map>
#include <unordered_map>

namespace Barrage
{
  typedef std::unordered_map<unsigned, PoolType> PoolTypeMap;
  typedef std::multimap<unsigned, Pool*> OrderedPoolMap;

  typedef void (*PoolUpdateFunc)(Pool*);
  typedef void (*InteractionFunc)(Pool*, Pool*);

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
          Applies the given function to all pools in the given group.

        \param group
          The key of the pool group.

        \param function
          The function to apply to these pools.
      */
      /**************************************************************/
      void UpdatePoolGroup(unsigned group, PoolUpdateFunc function);

      /**************************************************************/
      /*!
        \brief
          For each pool in group 1, applies the given function to all
          pools in group 2. 

        \param group1
          The key of the first pool group in the interaction.

        \param group2
          The key of the second pool group in the interaction.

        \param function
          The function to apply to these pools.
      */
      /**************************************************************/
      void UpdateInteraction(unsigned group1, unsigned group2, InteractionFunc function);

    protected:
      PoolTypeMap poolTypes_; //!< Holds all pool types the system cares about
      OrderedPoolMap pools_;  //!< Holds all subscribed pools in a specific order
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // BaseSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////