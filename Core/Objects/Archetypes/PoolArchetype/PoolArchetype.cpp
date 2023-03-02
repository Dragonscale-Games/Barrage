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
  PoolArchetype::PoolArchetype() :
    sharedComponents_(),
    componentArrayNames_(),
    tags_(),
    capacity_(1)
  {
  }

  PoolArchetype::PoolArchetype(const PoolArchetype& other) :
    sharedComponents_(),
    componentArrayNames_(other.componentArrayNames_),
    tags_(other.tags_),
    capacity_(other.capacity_)
  {
    CopyComponentMap(other.sharedComponents_);
  }

  PoolArchetype& PoolArchetype::operator=(const PoolArchetype& other)
  {
    componentArrayNames_ = other.componentArrayNames_;
    tags_ = other.tags_;
    capacity_ = other.capacity_;
    CopyComponentMap(other.sharedComponents_);

    return *this;
  }

  PoolArchetype::~PoolArchetype()
  {
    DeleteComponentMap();
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

  void PoolArchetype::RemoveComponentArray(const std::string_view& componentArrayName, unsigned* index)
  {
    for (auto it = componentArrayNames_.begin(); it != componentArrayNames_.end(); ++it)
    {
      if (*it == componentArrayName)
      {
        if (index)
        {
          *index = it - componentArrayNames_.begin();
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
          *index = it - tags_.begin();
        }

        tags_.erase(it);
        return;
      }
    }
  }

  void PoolArchetype::CopyComponentMap(const SharedComponentMap& other)
  {
    DeleteComponentMap();

    for (auto it = other.begin(); it != other.end(); ++it)
    {
      SharedComponent* newArray = ComponentAllocator::AllocateSharedComponent(it->first, it->second);

      if (newArray)
      {
        sharedComponents_[it->first] = newArray;
      }
    }
  }

  void PoolArchetype::DeleteComponentMap()
  {
    for (auto it = sharedComponents_.begin(); it != sharedComponents_.end(); ++it)
    {
      delete it->second;
    }

    sharedComponents_.clear();
  }
}
