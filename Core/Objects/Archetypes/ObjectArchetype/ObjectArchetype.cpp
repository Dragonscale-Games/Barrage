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
      const std::string_view& name = *it;

      ComponentArray* newArray = ComponentAllocator::AllocateComponentArray(name, 1);

      if (newArray && componentArrays_.count(name) == 0)
      {
        componentArrays_.insert(std::make_pair(name, newArray));
      }
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

  const ComponentArrayMap& ObjectArchetype::GetComponentArrays() const
  {
    return componentArrays_;
  }

  void ObjectArchetype::AddComponentArray(std::string_view name, ComponentArray* componentArray)
  {
    if (componentArrays_.count(name))
    {
      return;
    }

    componentArrays_.insert(std::make_pair(name, componentArray));
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

  void ObjectArchetype::CopyComponentArrayMap(const ComponentArrayMap& other)
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
}