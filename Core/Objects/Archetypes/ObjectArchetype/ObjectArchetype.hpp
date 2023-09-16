/* ======================================================================== */
/*!
 * \file            ObjectArchetype.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Used to initialize new objects by copying the values in its component map.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef ObjectArchetype_BARRAGE_H
#define ObjectArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Objects/Components/BaseClasses/ComponentArray.hpp>
#include <Serialization/Serializer.hpp>

namespace Barrage
{
  //! Used to initialize an object
  class ObjectArchetype
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Initializes the archetype with an empty map of components.
      */
      /**************************************************************/
      ObjectArchetype(const std::string& name, const std::vector<std::string_view>& componentArrayNames = std::vector<std::string_view>());

      /**************************************************************/
      /*!
        \brief
          Constructs the archetype using JSON data.

        \param data
          The JSON data to deserialize into this object.
      */
      /**************************************************************/
      ObjectArchetype(const rapidjson::Value& data);

      /**************************************************************/
      /*!
        \brief
          Copy constructor.

        \param other
          The archetype to copy.
      */
      /**************************************************************/
      ObjectArchetype(const ObjectArchetype& other);

      /**************************************************************/
      /*!
        \brief
          Copy assignment operator.

        \param other
          The archetype to copy.
      */
      /**************************************************************/
      ObjectArchetype& operator=(const ObjectArchetype& other);

      /**************************************************************/
      /*!
        \brief
          Deallocates all components attached to object archetype.
      */
      /**************************************************************/
      ~ObjectArchetype();

      /**************************************************************/
      /*!
        \brief
          Sets the name of the object archetype.

        \param newName
          The new name of the object archetype.
      */
      /**************************************************************/
      void SetName(const std::string& newName);

      /**************************************************************/
      /*!
        \brief
          Checks if the archetype contains a component array.

        \param name
          The name of the component array to check for.

        \return
          Returns true if the archetype contains the given component
          array, returns false otherwise.
      */
      /**************************************************************/
      bool HasComponentArray(const std::string_view& name) const;

      /**************************************************************/
      /*!
        \brief
          Gets the name of the object archetype.

        \return
          Returns the name of the object archetype.
      */
      /**************************************************************/
      const std::string& GetName() const;

      /**************************************************************/
      /*!
        \brief
          Gets the component array with the given name if it exists.

        \param name
          The name of the component array to get.

        \return
          Returns a pointer to the component array if it exists on
          the object archetype, returns nullptr otherwise.
      */
      /**************************************************************/
      ComponentArray* GetComponentArray(const std::string_view& name);

      /**************************************************************/
      /*!
        \brief
          Gets the component arrays of the object archetype.

        \return
          Returns the component arrays of the object archetype.
      */
      /**************************************************************/
      const ComponentArrayUmap& GetComponentArrays() const;

      /**************************************************************/
      /*!
        \brief
          Adds a component array to the object archetype. Has no effect
          if a component array with the given name already exists.

        \param name
          The name of the component array.

        \param componentArray
          The component array to add.
      */
      /**************************************************************/
      void AddComponentArray(std::string_view name, ComponentArray* componentArray);

      /**************************************************************/
      /*!
        \brief
          Removes and gets a component array from the object 
          archetype.

        \param name
          The name of the component array to extract.

        \return
          Returns a pointer to the extracted component array.
      */
      /**************************************************************/
      ComponentArray* ExtractComponentArray(std::string_view name);

      /**************************************************************/
      /*!
        \brief
          Serializes the object archetype into a rapidjson value.

        \return
          Returns the serialized rapidjson value.
      */
      /**************************************************************/
      rapidjson::Value Serialize(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator);

    private:
      /**************************************************************/
      /*!
        \brief
          Deep copies a component array map from "other" to "this".

        \param other
          The map to copy.
      */
      /**************************************************************/
      void CopyComponentArrayMap(const ComponentArrayUmap& other);

      /**************************************************************/
      /*!
        \brief
          Deep deletes this object's component array map.
      */
      /**************************************************************/
      void DeleteComponentArrayMap();

      /**************************************************************/
      /*!
        \brief
          Serializes the object archetype's component arrays into a 
          rapidjson value.

        \return
          Returns the serialized rapidjson value.
      */
      /**************************************************************/
      rapidjson::Value SerializeComponentArrays(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator);

      /**************************************************************/
      /*!
        \brief
          Deserializes a JSON of component arrays into this archetype.

        \param data
          The JSON of component arrays to deserialize.
      */
      /**************************************************************/
      void DeserializeComponentArrays(const rapidjson::Value& data);

    private:
      std::string name_;                   //!< A name for an object created with this archetype (for debug purposes, as objects don't have names)
      ComponentArrayUmap componentArrays_; //!< A map of initialized components to copy (each array has only one component)
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // ObjectArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////