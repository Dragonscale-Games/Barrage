/* ======================================================================== */
/*!
 * \file            ArchetypeManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Contains and manages all object and pool archetypes.
 */
/* ======================================================================== */

#include "stdafx.h"
#include "ArchetypeManager.hpp"

namespace Barrage
{
  ArchetypeManager::ArchetypeManager(ComponentAllocator& /*componentAllocator*/) :
    poolArchetypes_(),
    objectArchetypes_()//,
    //componentAllocator_(componentAllocator)
  {
  }

  ArchetypeManager::~ArchetypeManager()
  {
    for (auto it = poolArchetypes_.begin(); it != poolArchetypes_.end(); ++it)
    {
      delete it->second;
    }

    for (auto it = objectArchetypes_.begin(); it != objectArchetypes_.end(); ++it)
    {
      delete it->second;
    }
  }

  void ArchetypeManager::AddPoolArchetype(const std::string name, PoolArchetype* archetype)
  {
    if (poolArchetypes_.find(name) == poolArchetypes_.end())
    {
      poolArchetypes_[name] = archetype;
    }
    else
    {
      delete archetype;
    }
  }

  void ArchetypeManager::AddObjectArchetype(const std::string name, ObjectArchetype* archetype)
  {
    if (objectArchetypes_.find(name) == objectArchetypes_.end())
    {
      objectArchetypes_[name] = archetype;
    }
    else
    {
      delete archetype;
    }
  }

  PoolArchetype* ArchetypeManager::GetPoolArchetype(const std::string name)
  {
    if (poolArchetypes_.find(name) == poolArchetypes_.end())
    {
      return nullptr;
    }
    else
    {
      return poolArchetypes_.at(name);
    }
  }

  ObjectArchetype* ArchetypeManager::GetObjectArchetype(const std::string name)
  {
    if (objectArchetypes_.find(name) == objectArchetypes_.end())
    {
      return nullptr;
    }
    else
    {
      return objectArchetypes_.at(name);
    }
  }

  std::vector<std::string> ArchetypeManager::GetPoolArchetypeNames()
  {
    std::vector<std::string> archetype_list;

    for (auto it = poolArchetypes_.begin(); it != poolArchetypes_.end(); ++it)
    {
      archetype_list.push_back(it->first);
    }

    return archetype_list;
  }

  std::vector<std::string> ArchetypeManager::GetObjectArchetypeNames()
  {
    std::vector<std::string> archetype_list;

    for (auto it = objectArchetypes_.begin(); it != objectArchetypes_.end(); ++it)
    {
      archetype_list.push_back(it->first);
    }

    return archetype_list;
  }

  void ArchetypeManager::LoadPoolArchetype(const std::string name)
  {
    UNREFERENCED(name);
  }

  void ArchetypeManager::LoadObjectArchetype(const std::string name)
  {
    UNREFERENCED(name);
  }

  void ArchetypeManager::SavePoolArchetype(const std::string name)
  {
    UNREFERENCED(name);
  }

  void ArchetypeManager::SaveObjectArchetype(const std::string name)
  {
    UNREFERENCED(name);
  }
}