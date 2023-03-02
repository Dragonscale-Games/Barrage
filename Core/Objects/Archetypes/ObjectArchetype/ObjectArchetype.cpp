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
  ObjectArchetype::ObjectArchetype() :
    components_()
  {
  }

  ObjectArchetype::ObjectArchetype(const ObjectArchetype& other) :
    components_()
  {
    CopyComponentMap(other.components_);
  }

  ObjectArchetype& ObjectArchetype::operator=(const ObjectArchetype& other)
  {
    CopyComponentMap(other.components_);

    return *this;
  }

  ObjectArchetype::~ObjectArchetype()
  {
    DeleteComponentMap();
  }

  void ObjectArchetype::CopyComponentMap(const ComponentArrayMap& other)
  {
    DeleteComponentMap();

    for (auto it = other.begin(); it != other.end(); ++it)
    {
      ComponentArray* newArray = ComponentAllocator::AllocateComponentArray(it->first, 1);
      ComponentArray* otherArray = it->second;

      if (newArray)
      {
        newArray->CopyToThis(*otherArray, 0, 0);
        components_[it->first] = newArray;
      }
    }
  }

  void ObjectArchetype::DeleteComponentMap()
  {
    for (auto it = components_.begin(); it != components_.end(); ++it)
    {
      delete it->second;
    }

    components_.clear();
  }
}