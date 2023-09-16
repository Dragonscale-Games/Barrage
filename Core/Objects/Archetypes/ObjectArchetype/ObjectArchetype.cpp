/* ======================================================================== */
/*!
 * \file            ObjectArchetype.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Used to initialize new objects by copying the values in its component map.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "ObjectArchetype.hpp"
#include "Objects/Components/ComponentAllocator.hpp"

namespace Barrage
{
  ObjectArchetype::ObjectArchetype(const std::string& name, const std::vector<std::string_view>& componentArrayNames) :
    name_(name),
    componentArrays_()
  {
    for (auto it = componentArrayNames.begin(); it != componentArrayNames.end(); ++it)
    {
      const std::string_view& componentArrayName = *it;

      ComponentArray* newArray = ComponentAllocator::AllocateComponentArray(componentArrayName, 1);

      if (newArray && componentArrays_.count(componentArrayName) == 0)
      {
        componentArrays_.insert(std::make_pair(componentArrayName, newArray));
      }
    }
  }

  ObjectArchetype::ObjectArchetype(const rapidjson::Value& data) :
    name_("Unknown Object"),
    componentArrays_()
  {
    if (!data.IsObject())
    {
      return;
    }

    if (data.HasMember("Name") && data["Name"].IsString())
    {
      name_ = data["Name"].GetString();
    }

    if (data.HasMember("Components") && data["Components"].IsObject())
    {
      DeserializeComponentArrays(data["Components"]);
    }
  }

  ObjectArchetype::ObjectArchetype(const ObjectArchetype& other) :
    name_(other.name_),
    componentArrays_()
  {
    CopyComponentArrayMap(other.componentArrays_);
  }

  ObjectArchetype& ObjectArchetype::operator=(const ObjectArchetype& other)
  {
    name_ = other.name_;
    CopyComponentArrayMap(other.componentArrays_);

    return *this;
  }

  ObjectArchetype::~ObjectArchetype()
  {
    DeleteComponentArrayMap();
  }

  void ObjectArchetype::SetName(const std::string& newName)
  {
    name_ = newName;
  }

  bool ObjectArchetype::HasComponentArray(const std::string_view& name) const
  {
    return componentArrays_.count(name) > 0;
  }

  const std::string& ObjectArchetype::GetName() const
  {
    return name_;
  }

  ComponentArray* ObjectArchetype::GetComponentArray(const std::string_view& name)
  {
    if (componentArrays_.count(name) == 0)
    {
      return nullptr;
    }
    else
    {
      return componentArrays_.at(name);
    }
  }

  const ComponentArrayUmap& ObjectArchetype::GetComponentArrays() const
  {
    return componentArrays_;
  }

  void ObjectArchetype::AddComponentArray(std::string_view name, ComponentArray* componentArray)
  {
    std::string_view key = ComponentAllocator::GetComponentArrayLiteral(name);
    
    if (key.empty() || componentArrays_.count(key))
    {
      delete componentArray;
      return;
    }

    componentArrays_.insert(std::make_pair(key, componentArray));
  }

  ComponentArray* ObjectArchetype::ExtractComponentArray(std::string_view name)
  {
    if (componentArrays_.count(name) == 0)
    {
      return nullptr;
    }
    
    ComponentArray* componentArray = componentArrays_.at(name);
    componentArrays_.erase(name);

    return componentArray;
  }

  rapidjson::Value ObjectArchetype::Serialize(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator)
  {
    rapidjson::Value archetypeObject;
    archetypeObject.SetObject();

    rapidjson::Value nameValue(name_.c_str(), static_cast<rapidjson::SizeType>(name_.size()), allocator);
    archetypeObject.AddMember("Name", nameValue, allocator);

    rapidjson::Value componentsObject = SerializeComponentArrays(allocator);
    archetypeObject.AddMember("Components", componentsObject, allocator);

    return archetypeObject;
  }

  void ObjectArchetype::CopyComponentArrayMap(const ComponentArrayUmap& other)
  {
    DeleteComponentArrayMap();

    for (auto it = other.begin(); it != other.end(); ++it)
    {
      ComponentArray* newArray = ComponentAllocator::AllocateComponentArray(it->first, 1);
      newArray->CopyToThis(*it->second, 0, 0);
      componentArrays_[it->first] = newArray;
    }
  }

  void ObjectArchetype::DeleteComponentArrayMap()
  {
    for (auto it = componentArrays_.begin(); it != componentArrays_.end(); ++it)
    {
      delete it->second;
    }

    componentArrays_.clear();
  }

  rapidjson::Value ObjectArchetype::SerializeComponentArrays(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator)
  {
    rapidjson::Value componentsObject;
    componentsObject.SetObject();
    
    for (auto it = componentArrays_.begin(); it != componentArrays_.end(); ++it)
    {
      rapidjson::Value componentObject = Barrage::Serialize(it->second->GetRTTRValue(0), allocator);
      rapidjson::Value componentKey(it->first.data(), static_cast<rapidjson::SizeType>(it->first.size()), allocator);
      componentsObject.AddMember(componentKey, componentObject, allocator);
    }
    
    return componentsObject;
  }

  void ObjectArchetype::DeserializeComponentArrays(const rapidjson::Value& data)
  {
    for (auto it = data.MemberBegin(); it != data.MemberEnd(); ++it)
    {
      std::string name = it->name.GetString();
      
      ComponentArray* componentArray = ComponentAllocator::AllocateComponentArray(name, 1);

      if (componentArray)
      {
        rttr::type type = rttr::type::get_by_name(name);

        if (type.is_valid())
        {
          rttr::variant value = componentArray->GetRTTRValue(0);
          Barrage::Deserialize(value, it->value, type);
          componentArray->SetRTTRValue(value, 0);
        }
        
        AddComponentArray(name, componentArray);
      }
    }
  }
}