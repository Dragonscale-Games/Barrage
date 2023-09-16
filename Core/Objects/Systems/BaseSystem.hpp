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
#include <map>
#include <unordered_map>
#include <string_view>

namespace Barrage
{
  class SystemManager;
  class System;
  
  typedef std::unordered_map<std::string_view, PoolType> PoolTypeUmap;
  typedef std::map<std::string_view, std::vector<Pool*>> PoolGroupMap;

  typedef void (*PoolUpdateFunc)(Pool*);
  typedef void (*InteractionFunc)(Pool*, Pool*);
  typedef void (System::* PoolUpdateMemberFunc)(Pool*);
  typedef void (System::* InteractionMemberFunc)(Pool*, Pool*);

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
          Sets the system's parent manager.

        \param manager
          The parent manager of the system.
      */
      /**************************************************************/
      void SetSystemManager(SystemManager* manager);
      
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
      void UpdatePoolGroup(std::string_view group, PoolUpdateFunc function);

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
      void UpdatePoolGroup(std::string_view group, PoolUpdateMemberFunc function);

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
      void UpdateInteraction(std::string_view group1, std::string_view group2, InteractionFunc function);

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
      void UpdateInteraction(std::string_view group1, std::string_view group2, InteractionMemberFunc function);

    protected:
      PoolTypeUmap poolTypes_;        //!< Holds all pool types the system cares about
      PoolGroupMap poolGroups_;      //!< Holds all subscribed pools in a specific order
      SystemManager* systemManager_; //!< Holds all of a given Object Manager's systems (including this system)

    friend class SystemManager;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // BaseSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////