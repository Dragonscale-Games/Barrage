/* ======================================================================== */
/*!
 * \file            System.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base system class that all systems should inherit from.

   An system is a collection of related functions that perform operations
   on game objects. For instance, a movement system might contain all
   functions that change an object's position.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef System_BARRAGE_H
#define System_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "../Pools/Pool.hpp"
#include "../Pools/PoolType.hpp"

namespace Barrage
{
  class System;

  typedef std::map<std::string, PoolType, std::less<>> PoolTypeMap;
  typedef std::map<std::string, std::vector<Pool*>, std::less<>> PoolGroupMap;

  using PoolUpdateFunction = void (*)(Pool&);
  using InteractionFunction = void (*)(Pool&, Pool&);
  using PoolUpdateMemberFunction = void (System::*)(Pool&);
  using InteractionMemberFunction = void (System::*)(Pool&, Pool&);

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
      virtual void Unsubscribe(Pool* pool);

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
      void UpdatePoolGroup(const std::string& group, PoolUpdateFunction function);

      /**************************************************************/
      /*!
        \brief
          Applies the given system member function to all pools in
          the given group.

        \param group
          The key of the pool group.

        \param function
          The function to apply to these pools.
      */
      /**************************************************************/
      void UpdatePoolGroup(const std::string& group, PoolUpdateMemberFunction function);

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
      void UpdateInteraction(const std::string& group1, const std::string& group2, InteractionFunction function);

      /**************************************************************/
      /*!
        \brief
          For each pool in group 1, applies the given system member
          function to all pools in group 2.

        \param group1
          The key of the first pool group in the interaction.

        \param group2
          The key of the second pool group in the interaction.

        \param function
          The function to apply to these pools.
      */
      /**************************************************************/
      void UpdateInteraction(const std::string& group1, const std::string& group2, InteractionMemberFunction function);

    protected:
      PoolTypeMap poolTypes_;   //!< Holds all pool types the system cares about
      PoolGroupMap poolGroups_; //!< Holds all subscribed pools in a specific order
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // BaseSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////