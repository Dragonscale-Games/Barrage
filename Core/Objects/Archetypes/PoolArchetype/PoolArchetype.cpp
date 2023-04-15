/* ======================================================================== */
/*!
 * \file            PoolArchetype.cpp
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

#include "stdafx.h"
#include "PoolArchetype.hpp"
#include "Objects/Components/ComponentAllocator.hpp"

namespace Barrage
{
  PoolArchetype::PoolArchetype(const std::string& name, unsigned capacity) :
    name_(name),
    sharedComponents_(),
    componentArrayNames_(),
    tags_(),
    capacity_(capacity),
    startingObjects_(),
    spawnArchetypes_()
  {
  }

  PoolArchetype::PoolArchetype(const PoolArchetype& other) :
    name_(other.name_),
    sharedComponents_(),
    componentArrayNames_(other.componentArrayNames_),
    tags_(other.tags_),
    capacity_(other.capacity_),
    startingObjects_(other.startingObjects_),
    spawnArchetypes_(other.spawnArchetypes_)
  {
    CopySharedComponentMap(other.sharedComponents_);
  }

  PoolArchetype& PoolArchetype::operator=(const PoolArchetype& other)
  {
    name_ = other.name_;
    CopySharedComponentMap(other.sharedComponents_);
    componentArrayNames_ = other.componentArrayNames_;
    tags_ = other.tags_;
    capacity_ = other.capacity_;
    startingObjects_ = other.startingObjects_;
    spawnArchetypes_ = other.spawnArchetypes_;

    return *this;
  }

  PoolArchetype::~PoolArchetype()
  {
    DeleteSharedComponentMap();
  }

  bool PoolArchetype::HasComponentArray(const std::string_view& componentArrayName)
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

  bool PoolArchetype::HasTag(const std::string_view& tag)
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

  void PoolArchetype::RemoveComponentArray(const std::string_view& componentArrayName, unsigned* index)
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

  void PoolArchetype::CopySharedComponentMap(const SharedComponentMap& other)
  {
    DeleteSharedComponentMap();
    
    for (auto it = other.begin(); it != other.end(); ++it)
    {
      SharedComponent* newComponent = ComponentAllocator::AllocateSharedComponent(it->first);
      newComponent->CopyToThis(*it->second);
      sharedComponents_[it->first] = newComponent;
    }
  }

  void PoolArchetype::DeleteSharedComponentMap()
  {
    for (auto it = sharedComponents_.begin(); it != sharedComponents_.end(); ++it)
    {
      delete it->second;
    }

    sharedComponents_.clear();
  }
}