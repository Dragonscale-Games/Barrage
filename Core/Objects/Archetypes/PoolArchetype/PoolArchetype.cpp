/* ======================================================================== */
/*!
 * \file            PoolArchetype.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Used to initialize an object pool. Provides starting values of components
   on the pool. Only provides names of component arrays, as components in 
   component arrays are initialized later with an ObjectArchetype.
 */
/* ======================================================================== */

#include "stdafx.h"
#include "PoolArchetype.hpp"
#include "Objects/Components/ComponentAllocator.hpp"

namespace Barrage
{
  PoolArchetype::PoolArchetype(const std::string& name, unsigned capacity) :
    name_(name),
    capacity_(capacity),
    components_(),
    componentArrayNames_(),
    tags_(),
    startingObjects_(),
    spawnArchetypes_()
  {
  }

  PoolArchetype::PoolArchetype(const rapidjson::Value& data) :
    name_("Unknown Pool"),
    capacity_(1),
    components_(),
    componentArrayNames_(),
    tags_(),
    startingObjects_(),
    spawnArchetypes_()
  {
    if (!data.IsObject())
    {
      return;
    }

    if (data.HasMember("Name") && data["Name"].IsString())
    {
      name_ = data["Name"].GetString();
    }

    if (data.HasMember("Capacity") && data["Capacity"].IsUint())
    {
      capacity_ = data["Capacity"].GetUint();
    }

    if (data.HasMember("Components") && data["Components"].IsObject())
    {
      DeserializeComponents(data["Components"]);
    }

    if (data.HasMember("Component Arrays") && data["Component Arrays"].IsArray())
    {
      DeserializeComponentArrayNames(data["Component Arrays"]);
    }

    if (data.HasMember("Tags") && data["Tags"].IsArray())
    {
      DeserializeTags(data["Tags"]);
    }

    if (data.HasMember("Starting Objects") && data["Starting Objects"].IsArray())
    {
      DeserializeStartingObjects(data["Starting Objects"]);
    }

    if (data.HasMember("Spawn Archetypes") && data["Spawn Archetypes"].IsArray())
    {
      DeserializeSpawnArchetypes(data["Spawn Archetypes"]);
    }
  }

  PoolArchetype::PoolArchetype(const PoolArchetype& other) :
    name_(other.name_),
    components_(),
    componentArrayNames_(other.componentArrayNames_),
    tags_(other.tags_),
    capacity_(other.capacity_),
    startingObjects_(),
    spawnArchetypes_()
  {
    CopyComponentMap(other.components_);
    CopyStartingObjects(other.startingObjects_);
    CopySpawnArchetypes(other.spawnArchetypes_);
  }

  PoolArchetype& PoolArchetype::operator=(const PoolArchetype& other)
  {
    name_ = other.name_;
    CopyComponentMap(other.components_);
    componentArrayNames_ = other.componentArrayNames_;
    tags_ = other.tags_;
    capacity_ = other.capacity_;
    CopyStartingObjects(other.startingObjects_);
    CopySpawnArchetypes(other.spawnArchetypes_);

    return *this;
  }

  PoolArchetype::~PoolArchetype()
  {
    DeleteComponentMap();
  }

  bool PoolArchetype::HasObjectArchetype(const std::string& name)
  {
    return GetObjectArchetype(name) != nullptr;
  }

  bool PoolArchetype::HasComponent(const std::string_view& name)
  {
    return GetComponent(name) != nullptr;
  }

  bool PoolArchetype::HasComponentArray(const std::string_view& componentArrayName) const
  {
    for (auto it = componentArrayNames_.begin(); it != componentArrayNames_.end(); ++it)
    {
      if (*it == componentArrayName)
      {
        return true;
      }
    }

    return false;
  }

  bool PoolArchetype::HasTag(const std::string_view& tag) const
  {
    for (auto it = tags_.begin(); it != tags_.end(); ++it)
    {
      if (*it == tag)
      {
        return true;
      }
    }

    return false;
  }

  const std::string& PoolArchetype::GetName() const
  {
    return name_;
  }

  ObjectArchetype* PoolArchetype::GetObjectArchetype(const std::string& name)
  {
    for (auto it = startingObjects_.begin(); it != startingObjects_.end(); ++it)
    {
      ObjectArchetype* archetype = *it;

      if (archetype->GetName() == name)
      {
        return archetype;
      }
    }

    for (auto it = spawnArchetypes_.begin(); it != spawnArchetypes_.end(); ++it)
    {
      ObjectArchetype* archetype = *it;

      if (archetype->GetName() == name)
      {
        return archetype;
      }
    }
    
    return nullptr;
  }

  Component* PoolArchetype::GetComponent(const std::string_view& name)
  {
    if (components_.count(name))
    {
      return components_.at(name);
    }
    else
    {
      return nullptr;
    }
  }

  const ComponentMap& PoolArchetype::GetComponents() const
  {
    return components_;
  }

  const std::vector<std::string_view>& PoolArchetype::GetComponentArrayNames() const
  {
    return componentArrayNames_;
  }

  const std::vector<std::string_view>& PoolArchetype::GetTags() const
  {
    return tags_;
  }

  unsigned PoolArchetype::GetCapacity() const
  {
    return capacity_;
  }

  const std::vector<ObjectArchetype*>& PoolArchetype::GetStartingObjects() const
  {
    return startingObjects_;
  }

  const std::vector<ObjectArchetype*>& PoolArchetype::GetSpawnArchetypes() const
  {
    return spawnArchetypes_;
  }
  
  void PoolArchetype::SetCapacity(unsigned capacity)
  {
    capacity_ = capacity;

    if (capacity_ < 1)
    {
      capacity_ = 1;
    }
  }

  void PoolArchetype::AddComponent(const std::string_view& name, Component* sharedComponent)
  {
    std::string_view key = ComponentAllocator::GetComponentLiteral(name);

    if (key.empty() || components_.count(key))
    {
      delete sharedComponent;
      return;
    }

    components_.insert(std::make_pair(key, sharedComponent));
  }

  void PoolArchetype::AddComponentArrayName(const std::string_view& componentArrayName, unsigned* index)
  {
    std::string_view componentArrayLiteral = ComponentAllocator::GetComponentArrayLiteral(componentArrayName);

    if (componentArrayLiteral.empty())
    {
      return;
    }
    
    if (index && componentArrayNames_.size() > *index)
    {
      componentArrayNames_.insert(componentArrayNames_.begin() + *index, componentArrayLiteral);
    }
    else
    {
      componentArrayNames_.push_back(componentArrayLiteral);
    }
  }

  void PoolArchetype::AddTag(const std::string_view& tag, unsigned* index)
  {
    std::string_view tagLiteral = ComponentAllocator::GetTagLiteral(tag);

    if (tagLiteral.empty())
    {
      return;
    }
    
    if (index && tags_.size() > *index)
    {
      tags_.insert(tags_.begin() + *index, tagLiteral);
    }
    else
    {
      tags_.push_back(tagLiteral);
    }
  }

  void PoolArchetype::AddStartingObject(ObjectArchetype* archetype, unsigned* index)
  {
    if (!ObjectArchetypeIsValid(archetype) || HasObjectArchetype(archetype->GetName()))
    {
      delete archetype;
      return;
    }

    if (index && startingObjects_.size() > *index)
    {
      startingObjects_.insert(startingObjects_.begin() + *index, archetype);
    }
    else
    {
      startingObjects_.push_back(archetype);
    }
  }

  void PoolArchetype::AddSpawnArchetype(ObjectArchetype* archetype, unsigned* index)
  {
    if (!ObjectArchetypeIsValid(archetype) || HasObjectArchetype(archetype->GetName()))
    {
      delete archetype;
      return;
    }
    
    if (index && spawnArchetypes_.size() > *index)
    {
      spawnArchetypes_.insert(spawnArchetypes_.begin() + *index, archetype);
    }
    else
    {
      spawnArchetypes_.push_back(archetype);
    }
  }

  void PoolArchetype::RemoveComponentArrayName(const std::string_view& componentArrayName, unsigned* index)
  {
    for (auto it = componentArrayNames_.begin(); it != componentArrayNames_.end(); ++it)
    {
      if (*it == componentArrayName)
      {
        if (index)
        {
          *index = static_cast<unsigned>(it - componentArrayNames_.begin());
        }

        componentArrayNames_.erase(it);
        return;
      }
    }
  }

  void PoolArchetype::RemoveTag(const std::string_view& tag, unsigned* index)
  {
    for (auto it = tags_.begin(); it != tags_.end(); ++it)
    {
      if (*it == tag)
      {
        if (index)
        {
          *index = static_cast<unsigned>(it - tags_.begin());
        }

        tags_.erase(it);
        return;
      }
    }
  }

  ObjectArchetype* PoolArchetype::ExtractStartingObject(const std::string& name, unsigned* index)
  {
    for (auto it = startingObjects_.begin(); it != startingObjects_.end(); ++it)
    {
      ObjectArchetype* archetype = *it;
      
      if (archetype->GetName() == name)
      {
        if (index)
        {
          *index = static_cast<unsigned>(it - startingObjects_.begin());
        }

        startingObjects_.erase(it);

        return archetype;
      }
    }

    return nullptr;
  }

  Component* PoolArchetype::ExtractComponent(const std::string_view& name)
  {
    if (components_.count(name) == 0)
    {
      return nullptr;
    }
    
    Component* component = components_.at(name);
    components_.erase(name);
    return component;
  }

  rapidjson::Value PoolArchetype::Serialize(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator)
  {
    rapidjson::Value archetypeObject;
    archetypeObject.SetObject();

    rapidjson::Value nameValue(name_.c_str(), static_cast<rapidjson::SizeType>(name_.size()), allocator);
    archetypeObject.AddMember("Name", nameValue, allocator);

    archetypeObject.AddMember("Capacity", capacity_, allocator);

    rapidjson::Value componentsObject = SerializeComponents(allocator);
    archetypeObject.AddMember("Components", componentsObject, allocator);

    rapidjson::Value componentArrayNamesObject = SerializeStringViews(componentArrayNames_, allocator);
    archetypeObject.AddMember("Component Arrays", componentArrayNamesObject, allocator);

    rapidjson::Value tagsObject = SerializeStringViews(tags_, allocator);
    archetypeObject.AddMember("Tags", tagsObject, allocator);

    rapidjson::Value startingObjectsObject = SerializeObjectArchetypes(startingObjects_, allocator);
    archetypeObject.AddMember("Starting Objects", startingObjectsObject, allocator);

    rapidjson::Value spawnArchetypesObject = SerializeObjectArchetypes(spawnArchetypes_, allocator);
    archetypeObject.AddMember("Spawn Archetypes", spawnArchetypesObject, allocator);

    return archetypeObject;
  }

  void PoolArchetype::CopyComponentMap(const ComponentMap& other)
  {
    DeleteComponentMap();
    
    for (auto it = other.begin(); it != other.end(); ++it)
    {
      Component* newComponent = ComponentAllocator::AllocateComponent(it->first);
      newComponent->CopyToThis(*it->second);
      components_[it->first] = newComponent;
    }
  }

  void PoolArchetype::CopyStartingObjects(const std::vector<ObjectArchetype*>& other)
  {
    DeleteStartingObjects();

    for (auto it = other.begin(); it != other.end(); ++it)
    {
      startingObjects_.push_back(new ObjectArchetype(**it));
    }
  }

  void PoolArchetype::CopySpawnArchetypes(const std::vector<ObjectArchetype*>& other)
  {
    DeleteSpawnArchetypes();

    for (auto it = other.begin(); it != other.end(); ++it)
    {
      spawnArchetypes_.push_back(new ObjectArchetype(**it));
    }
  }

  void PoolArchetype::DeleteComponentMap()
  {
    for (auto it = components_.begin(); it != components_.end(); ++it)
    {
      delete it->second;
    }

    components_.clear();
  }

  void PoolArchetype::DeleteStartingObjects()
  {
    for (auto it = startingObjects_.begin(); it != startingObjects_.end(); ++it)
    {
      delete *it;
    }

    startingObjects_.clear();
  }

  void PoolArchetype::DeleteSpawnArchetypes()
  {
    for (auto it = spawnArchetypes_.begin(); it != spawnArchetypes_.end(); ++it)
    {
      delete *it;
    }

    spawnArchetypes_.clear();
  }

  rapidjson::Value PoolArchetype::SerializeComponents(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator)
  {
    rapidjson::Value componentsObject;
    componentsObject.SetObject();

    for (auto it = components_.begin(); it != components_.end(); ++it)
    {
      rapidjson::Value componentObject = Barrage::Serialize(it->second->GetRTTRValue(), allocator);
      rapidjson::Value componentKey(it->first.data(), static_cast<rapidjson::SizeType>(it->first.size()), allocator);
      componentsObject.AddMember(componentKey, componentObject, allocator);
    }

    return componentsObject;
  }

  rapidjson::Value PoolArchetype::SerializeStringViews(const std::vector<std::string_view>& strings, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator)
  {
    rapidjson::Value stringsArray;
    stringsArray.SetArray();

    for (auto it = strings.begin(); it != strings.end(); ++it)
    {
      rapidjson::Value string(it->data(), static_cast<rapidjson::SizeType>(it->size()), allocator);
      stringsArray.PushBack(string, allocator);
    }

    return stringsArray;
  }

  rapidjson::Value PoolArchetype::SerializeObjectArchetypes(const std::vector<ObjectArchetype*>& objects, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator)
  {
    rapidjson::Value objectArchetypeArray;
    objectArchetypeArray.SetArray();

    for (auto it = objects.begin(); it != objects.end(); ++it)
    {
      ObjectArchetype* archetype = *it;
      rapidjson::Value archetypeObject = archetype->Serialize(allocator);
      objectArchetypeArray.PushBack(archetypeObject, allocator);
    }

    return objectArchetypeArray;
  }

  void PoolArchetype::DeserializeComponents(const rapidjson::Value& data)
  {
    for (auto it = data.MemberBegin(); it != data.MemberEnd(); ++it)
    {
      std::string name = it->name.GetString();
      
      Component* component = ComponentAllocator::AllocateComponent(name);
    
      if (component)
      {
        rttr::type type = rttr::type::get_by_name(name);

        if (type.is_valid())
        {
          rttr::variant value = component->GetRTTRValue();
          Barrage::Deserialize(value, it->value, type);
          component->SetRTTRValue(value);
        }
        
        AddComponent(name, component);
      }
    }
  }

  void PoolArchetype::DeserializeComponentArrayNames(const rapidjson::Value& data)
  {
    for (auto it = data.Begin(); it != data.End(); ++it)
    {
      if (it->IsString())
      {
        std::string_view componentArrayLiteral = ComponentAllocator::GetComponentArrayLiteral(it->GetString());

        if (!componentArrayLiteral.empty())
        {
          componentArrayNames_.push_back(componentArrayLiteral);
        }
      }
    }
  }

  void PoolArchetype::DeserializeTags(const rapidjson::Value& data)
  {
    for (auto it = data.Begin(); it != data.End(); ++it)
    {
      if (it->IsString())
      {
        std::string_view tagLiteral = ComponentAllocator::GetTagLiteral(it->GetString());
    
        if (!tagLiteral.empty())
        {
          tags_.push_back(tagLiteral);
        }
      }
    }
  }

  void PoolArchetype::DeserializeStartingObjects(const rapidjson::Value& data)
  {
    for (auto it = data.Begin(); it != data.End(); ++it)
    {
      if (it->IsObject())
      {
        ObjectArchetype* objectArchetype = new ObjectArchetype(*it);
        AddStartingObject(objectArchetype);
      }
    }
  }

  void PoolArchetype::DeserializeSpawnArchetypes(const rapidjson::Value& data)
  {
    for (auto it = data.Begin(); it != data.End(); ++it)
    {
      if (it->IsObject())
      {
        ObjectArchetype* objectArchetype = new ObjectArchetype(*it);
        AddSpawnArchetype(objectArchetype);
      }
    }
  }

  bool PoolArchetype::ObjectArchetypeIsValid(ObjectArchetype* objectArchetype)
  {
    if (objectArchetype == nullptr)
    {
      return false;
    }
    
    for (auto it = componentArrayNames_.begin(); it != componentArrayNames_.end(); ++it)
    {
      if (!objectArchetype->HasComponentArray(*it))
      {
        return false;
      }
    }

    return true;
  }
}