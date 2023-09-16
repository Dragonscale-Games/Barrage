/* ======================================================================== */
/*!
 * \file            PoolArchetype.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Used to initialize an object pool. Provides starting values of components
   on the pool. Only provides names of component arrays, as components in
   component arrays are initialized later with an ObjectArchetype.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef PoolArchetype_BARRAGE_H
#define PoolArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/Component.hpp"
#include "Objects/Archetypes/ObjectArchetype/ObjectArchetype.hpp"
#include "Serialization/Serializer.hpp"

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
          Constructs the archetype using JSON data.

        \param data
          The JSON data to deserialize into this object.
      */
      /**************************************************************/
      PoolArchetype(const rapidjson::Value& data);

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
          Sets the name of the pool archetype.

        \param newName
          The new name of the pool archetype.
      */
      /**************************************************************/
      void SetName(const std::string& newName);

      /**************************************************************/
      /*!
        \brief
          Tells whether an object archetype with the given name 
          exists in the pool archetype's starting objects or spawn 
          archetypes.

        \param name
          The name of the object archetype.

        \return
          Returns true if the object archetype exists, returns false
          otherwise.
      */
      /**************************************************************/
      bool HasObjectArchetype(const std::string& name);

      /**************************************************************/
      /*!
        \brief
          Checks if the archetype contains a component with the 
          given name.

        \param name
          The name of the component to check for.

        \return
          Returns true if the archetype contains the component, 
          returns false otherwise.
      */
      /**************************************************************/
      bool HasComponent(const std::string_view& name);

      /**************************************************************/
      /*!
        \brief
          Checks if the archetype contains a component array with the
          given name.

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
          Checks if the archetype contains a given tag.

        \param tag
          The name of the tag to check for.

        \return
          Returns true if the archetype contains the given tag,
          returns false otherwise.
      */
      /**************************************************************/
      bool HasTag(const std::string_view& tag) const;

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
          Gets the object archetype with the given name if it exists
          in the pool archetype's starting objects or spawn
          archetypes.

        \param name
          The name of the object archetype.

        \return
          Returns the object archetype if it exists, returns nullptr
          otherwise.
      */
      /**************************************************************/
      ObjectArchetype* GetObjectArchetype(const std::string& name);

      /**************************************************************/
      /*!
        \brief
          Gets the component with the given name if it exists.

        \param name
          The name of the component.

        \return
          Returns the component if it exists, returns nullptr
          otherwise.
      */
      /**************************************************************/
      Component* PoolArchetype::GetComponent(const std::string_view& name);

      /**************************************************************/
      /*!
        \brief
          Gets the pool archetype's components.

        \return
          Returns the pool archetype's components.
      */
      /**************************************************************/
      const ComponentUmap& GetComponents() const;

      /**************************************************************/
      /*!
        \brief
          Gets the names of the pool archetype's component arrays.

        \return
          Returns the names of the pool archetype's component arrays.
      */
      /**************************************************************/
      const std::vector<std::string_view>& GetComponentArrayNames() const;

      /**************************************************************/
      /*!
        \brief
          Gets the pool archetype's tags.

        \return
          Returns the pool archetype's tags.
      */
      /**************************************************************/
      const std::vector<std::string_view>& GetTags() const;

      /**************************************************************/
      /*!
        \brief
          Gets the capacity of the pool archetype.

        \return
          Returns the capacity of the pool archetype.
      */
      /**************************************************************/
      unsigned GetCapacity() const;

      /**************************************************************/
      /*!
        \brief
          Gets the capacity of the pool archetype.

        \return
          Returns the capacity of the pool archetype.
      */
      /**************************************************************/
      const std::vector<ObjectArchetype*>& GetStartingObjects() const;

      /**************************************************************/
      /*!
        \brief
          Gets the capacity of the pool archetype.

        \return
          Returns the capacity of the pool archetype.
      */
      /**************************************************************/
      const std::vector<ObjectArchetype*>& GetSpawnArchetypes() const;

      /**************************************************************/
      /*!
        \brief
          Sets the capacity of the pool archetype.

        \param capacity
          The new capacity of the pool.
      */
      /**************************************************************/
      void SetCapacity(unsigned capacity);

      /**************************************************************/
      /*!
        \brief
          Adds a component to the pool archetype. Has no effect
          if a component with the given name already exists.

        \param name
          The name of the component.

        \param component
          The component to add.
      */
      /**************************************************************/
      void AddComponent(const std::string_view& name, Component* component);

      /**************************************************************/
      /*!
        \brief
          Adds a component array name to the archetype.

        \param name
          The name of the component array to add.

        \param index
          Optional, allows the name to be inserted at a specific index
          in the vector.
      */
      /**************************************************************/
      void AddComponentArrayName(const std::string_view& name, unsigned* index = nullptr);

      /**************************************************************/
      /*!
        \brief
          Adds a tag to the archetype.

        \param tag
          The name of the tag to add.

        \param index
          Optional, allows the tag to be inserted at a specific index
          in the vector.
      */
      /**************************************************************/
      void AddTag(const std::string_view& tag, unsigned* index = nullptr);

      /**************************************************************/
      /*!
        \brief
          Adds a starting object to the pool archetype.

        \param archetype
          The object archetype to add.

        \param index
          Optional, allows the tag to be inserted at a specific index
          in the vector.
      */
      /**************************************************************/
      void AddStartingObject(ObjectArchetype* archetype, unsigned* index = nullptr);

      /**************************************************************/
      /*!
        \brief
          Adds a spawn archetype to the pool archetype.

        \param archetype
          The spawn archetype to add.

        \param index
          Optional, allows the tag to be inserted at a specific index
          in the vector.
      */
      /**************************************************************/
      void AddSpawnArchetype(ObjectArchetype* archetype, unsigned* index = nullptr);

      /**************************************************************/
      /*!
        \brief
          Removes a component array name from the archetype.

        \param componentArrayName
          The name of the component array to remove.

        \param index
          The index of the component array in the underlying vector
          will be written to this variable if the component array
          was removed. Otherwise, this variable will be unchanged.
      */
      /**************************************************************/
      void RemoveComponentArrayName(const std::string_view& componentArrayName, unsigned* index = nullptr);

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

      /**************************************************************/
      /*!
        \brief
          Removes and gets a starting object archetype from the pool
          archetype.

        \param name
          The name of the starting object archetype to extract.

        \param index
          The index of the starting object in the underlying vector 
          will be written to this variable if the tag was removed. 
          Otherwise, this variable will be unchanged.
      */
      /**************************************************************/
      ObjectArchetype* ExtractStartingObject(const std::string& name, unsigned* index = nullptr);

      /**************************************************************/
      /*!
        \brief
          Removes and gets a spawn archetype from the pool
          archetype.

        \param name
          The name of the spawn archetype to extract.

        \param index
          The index of the spawn archetype in the underlying vector
          will be written to this variable if the archetype was removed.
          Otherwise, this variable will be unchanged.
      */
      /**************************************************************/
      ObjectArchetype* ExtractSpawnArchetype(const std::string& name, unsigned* index = nullptr);

      /**************************************************************/
      /*!
        \brief
          Removes and returns a component from the pool archetype if 
          it exists.

        \param name
          The name of the component to extract.

        \return
          Returns a pointer to the component if it exists, returns 
          nullptr otherwise.
      */
      /**************************************************************/
      Component* ExtractComponent(const std::string_view& name);

      /**************************************************************/
      /*!
        \brief
          Serializes the pool archetype into a rapidjson value.

        \return
          Returns the serialized rapidjson value.
      */
      /**************************************************************/
      rapidjson::Value Serialize(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator);

    private:
      /**************************************************************/
      /*!
        \brief
          Removes and gets the object with the given name from the
          given object vector.

        \param objectVector
          The vector to extract the object from.

        \param name
          The name of the object to extract.

        \param index
          The index of the object in the underlying vector
          will be written to this variable if the object was removed.
          Otherwise, this variable will be unchanged.
      */
      /**************************************************************/
      ObjectArchetype* ExtractObject(std::vector<ObjectArchetype*>& objectVector, const std::string& name, unsigned* index = nullptr);
      
      /**************************************************************/
      /*!
        \brief
          Deep copies a component map from "other" to "this".

        \param other
          The map to copy.
      */
      /**************************************************************/
      void CopyComponentMap(const ComponentUmap& other);

      /**************************************************************/
      /*!
        \brief
          Deep copies a starting object vector from "other" to "this".

        \param other
          The vector to copy.
      */
      /**************************************************************/
      void CopyStartingObjects(const std::vector<ObjectArchetype*>& other);

      /**************************************************************/
      /*!
        \brief
          Deep copies a spawn archetype vector from "other" to "this".

        \param other
          The vector to copy.
      */
      /**************************************************************/
      void CopySpawnArchetypes(const std::vector<ObjectArchetype*>& other);

      /**************************************************************/
      /*!
        \brief
          Deep deletes this archetype's component map.
      */
      /**************************************************************/
      void DeleteComponentMap();

      /**************************************************************/
      /*!
        \brief
          Deep deletes this object's starting object vector.
      */
      /**************************************************************/
      void DeleteStartingObjects();

      /**************************************************************/
      /*!
        \brief
          Deep deletes this object's spawn archetype vector.
      */
      /**************************************************************/
      void DeleteSpawnArchetypes();

      /**************************************************************/
      /*!
        \brief
          Serializes the pool archetype's components into a
          rapidjson value.

        \return
          Returns the serialized rapidjson value.
      */
      /**************************************************************/
      rapidjson::Value SerializeComponents(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator);

      /**************************************************************/
      /*!
        \brief
          Serializes a vector of string_views into a rapidjson
          value.

        \param strings
          The string_view vector to serialize.

        \return
          Returns the serialized rapidjson value.
      */
      /**************************************************************/
      rapidjson::Value SerializeStringViews(const std::vector<std::string_view>& strings, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator);

      /**************************************************************/
      /*!
        \brief
          Serializes a vector of object archetypes into a rapidjson
          value.

        \param objects
          The object archetype vector to serialize.

        \return
          Returns the serialized rapidjson value.
      */
      /**************************************************************/
      rapidjson::Value SerializeObjectArchetypes(const std::vector<ObjectArchetype*>& objects, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator);

      /**************************************************************/
      /*!
        \brief
          Deserializes a JSON of components into this archetype.

        \param data
          The JSON of components to deserialize.
      */
      /**************************************************************/
      void DeserializeComponents(const rapidjson::Value& data);

      /**************************************************************/
      /*!
        \brief
          Deserializes a JSON of component array names into this 
          archetype.

        \param data
          The JSON of component array names to deserialize.
      */
      /**************************************************************/
      void DeserializeComponentArrayNames(const rapidjson::Value& data);

      /**************************************************************/
      /*!
        \brief
          Deserializes a JSON of tags into this archetype.

        \param data
          The JSON of tags to deserialize.
      */
      /**************************************************************/
      void DeserializeTags(const rapidjson::Value& data);

      /**************************************************************/
      /*!
        \brief
          Deserializes a JSON of starting objects into this archetype.

        \param data
          The JSON of starting objects to deserialize.
      */
      /**************************************************************/
      void DeserializeStartingObjects(const rapidjson::Value& data);

      /**************************************************************/
      /*!
        \brief
          Deserializes a JSON of spawn archetypes into this archetype.

        \param data
          The JSON of spawn archetypes to deserialize.
      */
      /**************************************************************/
      void DeserializeSpawnArchetypes(const rapidjson::Value& data);

      /**************************************************************/
      /*!
        \brief
          Determines whether an object archetype has the component
          arrays expected by the pool.

        \param objectArchetype
          The object archetype to validate.

        \return
          Returns true if the object archetype's component arrays 
          match the pool's, returns false otherwise.
      */
      /**************************************************************/
      bool ObjectArchetypeIsValid(ObjectArchetype* objectArchetype);

    private:
      std::string name_;                                  //!< Name of the pool this archetype will create
      unsigned capacity_;                                 //!< The number of objects the pool will be able to hold
      ComponentUmap components_;                          //!< Initialized components to copy to the pool
      std::vector<std::string_view> componentArrayNames_; //!< Names of the pool's component arrays
      std::vector<std::string_view> tags_;                //!< Tags of the pool

      std::vector<ObjectArchetype*> startingObjects_;     //!< The objects the pool starts with
      std::vector<ObjectArchetype*> spawnArchetypes_;     //!< Objects that can be spawned in the pool
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // PoolArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////