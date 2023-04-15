/* ======================================================================== */
/*!
 * \file            PoolArchetype.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Used to initialize an object pool. Provides starting values of shared
   components using its shared component map. Only provides names of component
   arrays, as components in component arrays are initialized later with an
   ObjectArchetype.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef PoolArchetype_BARRAGE_H
#define PoolArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/EngineComponents.hpp"
#include "Objects/Archetypes/ObjectArchetype/ObjectArchetype.hpp"

namespace Barrage
{
  //! Used to initialize an object pool
  class PoolArchetype
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the pool archetype.

        \param name
          The name of the pool this archetype will create.
      */
      /**************************************************************/
      PoolArchetype(const std::string& name, unsigned capacity = 1);

      /**************************************************************/
      /*!
        \brief
          Copy constructor.

        \param other
          The archetype to copy.
      */
      /**************************************************************/
      PoolArchetype(const PoolArchetype& other);

      /**************************************************************/
      /*!
        \brief
          Copy assignment operator.

        \param other
          The archetype to copy.
      */
      /**************************************************************/
      PoolArchetype& operator=(const PoolArchetype& other);

      /**************************************************************/
      /*!
        \brief
          Deallocates all components attached to pool archetype.
      */
      /**************************************************************/
      ~PoolArchetype();

      /**************************************************************/
      /*!
        \brief
          Checks if the archetype contains a component array.

        \param componentArrayName
          The name of the component array to check for.

        \return
          Returns true if the archetype contains the given component
          array, returns false otherwise.
      */
      /**************************************************************/
      bool HasComponentArray(const std::string_view& componentArrayName);

      /**************************************************************/
      /*!
        \brief
          Checks if the archetype contains a given tag.

        \param tag
          The name of the tag to check for.

        \return
          Returns true if the archetype contains the given tag,
          returns false otherwise.
      */
      /**************************************************************/
      bool HasTag(const std::string_view& tag);

      /**************************************************************/
      /*!
        \brief
          Removes a component array from the archetype.

        \param componentArrayName
          The name of the component array to remove.

        \param index
          The index of the component array in the underlying vector
          will be written to this variable if the component array
          was removed. Otherwise, this variable will be unchanged.
      */
      /**************************************************************/
      void RemoveComponentArray(const std::string_view& componentArrayName, unsigned* index = nullptr);

      /**************************************************************/
      /*!
        \brief
          Removes a tag from the archetype.

        \param tag
          The name of the tag to remove.

        \param index
          The index of the tag in the underlying vector will be
          written to this variable if the tag was removed. Otherwise,
          this variable will be unchanged.
      */
      /**************************************************************/
      void RemoveTag(const std::string_view& tag, unsigned* index = nullptr);

    private:
      /**************************************************************/
      /*!
        \brief
          Deep copies a shared component map from "other" to "this".

        \param other
          The map to copy.
      */
      /**************************************************************/
      void CopySharedComponentMap(const SharedComponentMap& other);

      /**************************************************************/
      /*!
        \brief
          Deep deletes this object's shared component map.
      */
      /**************************************************************/
      void DeleteSharedComponentMap();

    public:
      std::string name_;                                  //!< Name of the pool this archetype will create
      SharedComponentMap sharedComponents_;               //!< Initialized shared components to copy to the pool
      std::vector<std::string_view> componentArrayNames_; //!< Names of the pool's component arrays
      std::vector<std::string_view> tags_;                //!< Tags of the pool
      unsigned capacity_;                                 //!< The number of objects the pool will be able to hold
      std::vector<ObjectArchetype> startingObjects_;      //!< The objects the pool starts with
      std::vector<ObjectArchetype> spawnArchetypes_;      //!< Objects that can be spawned in the pool
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // PoolArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////