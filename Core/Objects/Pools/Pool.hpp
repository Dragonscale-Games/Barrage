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

#include "Objects/Archetypes/PoolArchetype.hpp"
#include "Objects/Components/Component.hpp"
#include "Objects/Components/ComponentArray.hpp"
#include "Objects/Spawning/SpawnType.hpp"

namespace Barrage
{
  //! Container for a prespecified number of objects
  class Pool
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs an object pool.

        \param archetype
          The archetype to construct the pool from.
      */
      /**************************************************************/
      Pool(const PoolArchetype& archetype);

      /**************************************************************/
      /*!
        \brief
          Gets the number of active objects.

        \return
          Returns the number of active objects.
      */
      /**************************************************************/
      unsigned ActiveObjectCount() const;

      /**************************************************************/
      /*!
        \brief
          Gets the number of objects the pool can hold.

        \return
          Returns the number of objects the pool can hold.
      */
      /**************************************************************/
      unsigned GetCapacity() const;

      /**************************************************************/
      /*!
        \brief
          Get a reference to a given component. Throws an
          out_of_range exception if no component matches the
          input name.

        \tparam T
          The type of component to get.

        \param componentName
          The name of the component to get.

        \return
          Returns a reference to the component with the given name.
      */
      /**************************************************************/
      template <typename T>
      ComponentT<T>& GetComponent(const std::string& componentName);

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
      ComponentArrayT<T>& GetComponentArray(const std::string& componentArrayName);

      /**************************************************************/
      /*!
        \brief
          Creates new objects and queues them for spawn. The objects
          are later spawned when SpawnObjects() is called.

        \param space
          The space the source and destination pools live in.

        \param sourcePool
          The pool spawning the objects.

        \param spawnType
          Contains the information needed to spawn the objects.
      */
      /**************************************************************/
      void QueueSpawns(Space& space, Pool& sourcePool, SpawnType& spawnType);

      /**************************************************************/
      /*!
        \brief
          Spawns all objects queued for spawn.
      */
      /**************************************************************/
      void SpawnObjects();

      /**************************************************************/
      /*!
        \brief
          Determines if the pool has a given  component.

        \param componentName
          The name of the component to check for.

        \return
          Returns true if the pool has the component, returns
          false otherwise.
      */
      /**************************************************************/
      bool HasComponent(const std::string& componentName);

      /**************************************************************/
      /*!
        \brief
          Determines if the pool has a given component array.

        \param componentArrayName
          The name of the component array to check for.

        \return
          Returns true if the pool has the component array, returns
          false otherwise.
      */
      /**************************************************************/
      bool HasComponentArray(const std::string& componentArrayName);

      /**************************************************************/
      /*!
        \brief
          Determines if the pool has a given tag.

        \param tag
          The tag to check for.

        \return
          Returns true if the pool has the tag, returns false
          otherwise.
      */
      /**************************************************************/
      bool HasTag(const std::string& tag) const;

    private:
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
          Gets the index of the first available object slot.

        \return
          Returns the index of the first available object slot.
      */
      /**************************************************************/
      unsigned GetSpawnIndex() const;

      /**************************************************************/
      /*!
        \brief
          Creates a number of objects in the pool by copying an
          object archetype.

          SAFETY:
          This function assumes numObjects <= available slots.

        \param archetype
          The archetype used to construct the objects.

        \param numObjects
          The number of objects to create.
      */
      /**************************************************************/
      void CreateObjectsUnsafe(const ObjectArchetype& archetype, unsigned numObjects);

      void ApplyValueSpawnRules(Space& space, Pool& sourcePool, SpawnType& spawnType, unsigned numObjects);

      void ApplySizeSpawnRules(Space& space, Pool& sourcePool, SpawnType& spawnType, unsigned numObjects);

    public:
      ComponentMap components_;            //!< Holds shared components and their names
      ComponentArrayMap componentArrays_;  //!< Holds component arrays and their names
      StringSet tags_;                     //!< Holds the pool's tags
      ObjectArchetypeMap spawnArchetypes_; //!< Objects that can be spawned in this pool
      unsigned numActiveObjects_;          //!< Number of currently active objects
      unsigned numQueuedObjects_;          //!< Number of objects ready to be spawned on the next tick
      unsigned capacity_;                  //!< Total number of objects the pool can hold
      std::string name_;                   //!< Name of the pool
  };

  using PoolMap = std::map<std::string, Pool>;
}

#include "Pool.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // Pool_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////