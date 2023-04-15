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
    startingObjects_(),
    spawnArchetypes_()
  {
    CopySharedComponentMap(other.sharedComponents_);
    CopyStartingObjects(other.startingObjects_);
    CopySpawnArchetypes(other.spawnArchetypes_);
  }

  PoolArchetype& PoolArchetype::operator=(const PoolArchetype& other)
  {
    name_ = other.name_;
    CopySharedComponentMap(other.sharedComponents_);
    componentArrayNames_ = other.componentArrayNames_;
    tags_ = other.tags_;
    capacity_ = other.capacity_;
    CopyStartingObjects(other.startingObjects_);
    CopySpawnArchetypes(other.spawnArchetypes_);

    return *this;
  }

  PoolArchetype::~PoolArchetype()
  {
    DeleteSharedComponentMap();
  }

  const std::string& PoolArchetype::GetName() const
  {
    return name_;
  }

  const SharedComponentMap& PoolArchetype::GetSharedComponents() const
  {
    return sharedComponents_;
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
  
  void PoolArchetype::AddSharedComponent(std::string_view name, SharedComponent* sharedComponent)
  {
    if (sharedComponents_.count(name))
    {
      return;
    }

    sharedComponents_.insert(std::make_pair(name, sharedComponent));
  }

  void PoolArchetype::AddComponentArrayName(const std::string_view& componentArrayName, unsigned* index)
  {
    if (index && componentArrayNames_.size() > *index)
    {
      componentArrayNames_.insert(componentArrayNames_.begin() + *index, componentArrayName);
    }
    else
    {
      componentArrayNames_.push_back(componentArrayName);
    }
  }

  void PoolArchetype::AddTag(const std::string_view& tag, unsigned* index)
  {
    if (index && tags_.size() > *index)
    {
      tags_.insert(tags_.begin() + *index, tag);
    }
    else
    {
      tags_.push_back(tag);
    }
  }

  void PoolArchetype::AddStartingObject(ObjectArchetype* archetype, unsigned* index)
  {
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

  void PoolArchetype::DeleteSharedComponentMap()
  {
    for (auto it = sharedComponents_.begin(); it != sharedComponents_.end(); ++it)
    {
      delete it->second;
    }

    sharedComponents_.clear();
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
}