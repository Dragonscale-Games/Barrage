/* ======================================================================== */
/*!
 * \file            Pool.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   An object pool is a block of memory that can hold a prespecified number
   of objects with a specific combination of components.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Pool_BARRAGE_H
#define Pool_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/SharedComponent.hpp"
#include "Objects/Components/BaseClasses/ComponentArray.hpp"
#include "Objects/Archetypes/ObjectArchetype/ObjectArchetype.hpp"
#include "Objects/Spawning/SpawnInfo.hpp"

#include <unordered_set>
#include <unordered_map>

namespace Barrage
{
  typedef std::unordered_set<std::string_view> TagSet;
  typedef std::unordered_map<std::string, ObjectArchetype> SpawnArchetypeMap;
  
  class Space;

  //! Container for a prespecified number of objects
  class Pool
  {
    public:  
      /**************************************************************/
      /*!
        \brief
          Constructs an object pool.

        \param name
          The name of the pool (for debugging).

        \param capacity
          The number of objects the pool will be able to hold.

        \param space
          The space the pool lives in.
      */
      /**************************************************************/
      Pool(const std::string& name, unsigned capacity, Space& space);
      
      Pool(const Pool& other) = delete;

      Pool& operator=(const Pool& other) = delete;
      
      /**************************************************************/
      /*!
        \brief
          Deallocates all components attached to the pool.
      */
      /**************************************************************/
      ~Pool();

      /**************************************************************/
      /*!
        \brief
          Adds a tag to the pool.

        \param name
          The name of the tag to add.
      */
      /**************************************************************/
      void AddTag(const std::string_view& name);

      /**************************************************************/
      /*!
        \brief
          Adds a component array to the pool whose capacity matches
          the pool's.

        \param name
          The name of the component array to add. It must have been
          previously registered in the component allocator, or this
          function has no effect.
      */
      /**************************************************************/
      void AddComponentArray(const std::string_view& name);

      /**************************************************************/
      /*!
        \brief
          Adds a shared component to the pool. Initial values can be
          optionally set by an initializer.

        \param name
          The name of the shared component to add. It must have been
          previously registered in the component allocator, or this
          function has no effect.
      */
      /**************************************************************/
      void AddSharedComponent(const std::string_view& name, SharedComponent* initializer = nullptr);

      /**************************************************************/
      /*!
        \brief
          Adds a spawn archetype to the pool.

        \param spawnArchetype
          The spawn archetype to add.
      */
      /**************************************************************/
      void AddSpawnArchetype(const ObjectArchetype& spawnArchetype);

      /**************************************************************/
      /*!
        \brief
          Creates a given number of active objects in the pool from
          an object archetype. This should generally only be used
          on scene creation; QueueSpawns() should be used while the
          scene is running.

        \param archetype
          The archetype used to construct the objects.

        \param numObjects
          The number of objects to create. If this would overfill the
          pool, the excess objects are not created.
      */
      /**************************************************************/
      void CreateObject(const ObjectArchetype& archetype);

      /**************************************************************/
      /*!
        \brief
          Queues a number of objects for spawning on the next creation 
          system update.

        \param sourcePool
          The pool spawning the objects.

        \param spawnInfo
          Contains the information needed to spawn the objects.
      */
      /**************************************************************/
      void QueueSpawns(Pool* sourcePool, SpawnInfo& spawnInfo);

      /**************************************************************/
      /*!
        \brief
          Determines if a pool has a given tag.

        \param tag
          The tag to check for.

        \return
          Returns true if the pool has the tag, returns false
          otherwise.
      */
      /**************************************************************/
      bool HasTag(const std::string_view& tag) const;

      /**************************************************************/
      /*!
        \brief
          Determines if a pool has a given component array.

        \param componentArrayName
          The name of the component array to check for.

        \return
          Returns true if the pool has the component array, returns 
          false otherwise.
      */
      /**************************************************************/
      bool HasComponentArray(const std::string_view& componentArrayName);

      /**************************************************************/
      /*!
        \brief
          Determines if a pool has a given shared component.

        \param sharedComponentName
          The name of the shared component to check for.

        \return
          Returns true if the pool has the shared component, returns
          false otherwise.
      */
      /**************************************************************/
      bool HasSharedComponent(const std::string_view& sharedComponentName);

      /**************************************************************/
      /*!
        \brief
          Gets the number of available object slots in the pool.

        \return
          Returns the number of available object slots in the pool.
      */
      /**************************************************************/
      unsigned GetAvailableSlots() const;

      /**************************************************************/
      /*!
        \brief
          Gets the number of active objects.

        \return
          Returns the number of active objects.
      */
      /**************************************************************/
      unsigned GetActiveObjectCount() const;
      
      /**************************************************************/
      /*!
        \brief
          Gets the number of objects queued for spawn.

        \return
          Returns the number of objects queued for spawn.
      */
      /**************************************************************/
      unsigned GetQueuedObjectCount() const;

      /**************************************************************/
      /*!
        \brief
          Get a reference to a given component array. Throws an
          out_of_range exception if no component array matches the
          input name.

        \tparam T
          The type of component array to get.

        \param componentName
          The name of the component array to get.

        \return
          Returns a reference to the component array with the given
          name.
      */
      /**************************************************************/
      template <typename T>
      ComponentArrayT<T>* GetComponentArray(const std::string_view& componentName);

      /**************************************************************/
      /*!
        \brief
          Get a reference to a given shared component. Throws an
          out_of_range exception if no shared component matches the
          input name.

        \tparam T
          The type of shared component to get.

        \param componentName
          The name of the shared component to get.

        \return
          Returns a reference to the shared component with the given
          name.
      */
      /**************************************************************/
      template <typename T>
      SharedComponentT<T>* GetSharedComponent(const std::string_view& componentName);

      /**************************************************************/
      /*!
        \brief
          Gets the spawn archetype with the given name. Throws an
          out_of_range exception if no spawn archetype matches the
          input name.

        \param index
          The index of the spawn archetype.

        \return
          Returns a reference to the spawn archetype with the given
          name.
      */
      /**************************************************************/
      const ObjectArchetype& GetSpawnArchetype(const std::string& name) const;

    private:
      /**************************************************************/
      /*!
        \brief
          Shifts all queued objects to the right by some number of
          places. Used to make room for active objects if they are
          being created directly.

        \param numberOfPlaces
          The number of places to shift the queued objects to the
          right in the array.
      */
      /**************************************************************/
      void ShiftQueuedObjects(unsigned numberOfPlaces);

      /**************************************************************/
      /*!
        \brief
          Copies an object archetype to a range of objects in the
          pool.

        \param archetype
          The archetype used to construct the objects.

        \param startIndex
          The index of the first new object.

        \param numObjects
          The number of objects to create.
      */
      /**************************************************************/
      void CreateObjectsInternal(const ObjectArchetype& archetype, unsigned startIndex, unsigned numObjects);

      /**************************************************************/
      /*!
        \brief
          Applies spawn functions to newly spawned objects in this
          pool.

        \param spawnInfo
          Contains the spawn function list and source object indices.

        \param startIndex
          The index of the first object to apply spawn functions to.

        \param numObjects
          The number of objects to apply spawn functions to.
      */
      /**************************************************************/
      void ApplySpawnFuncs(Pool* sourcePool, const SpawnInfo& spawnInfo, unsigned startIndex, unsigned numObjects);

    private:
      ComponentArrayMap componentArrays_;   //!< Holds component arrays and their names
      SharedComponentMap sharedComponents_; //!< Holds shared components and their names
      SpawnArchetypeMap spawnArchetypes_;   //!< Objects that can be spawned in the pool
      TagSet tags_;                         //!< Holds the pool's tags
      unsigned numActiveObjects_;           //!< Number of currently active objects
      unsigned numQueuedObjects_;           //!< Number of objects waiting to be spawned on the next tick
      const unsigned capacity_;             //!< Total number of objects the pool can hold
      std::string name_;                    //!< Name of the pool
      Space& space_;                        //!< The space the pool lives in

      friend class CreationSystem;
      friend class DestructionSystem;
  };
}

#include "Pool.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // Pool_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////