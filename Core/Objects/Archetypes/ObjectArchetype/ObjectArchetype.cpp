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
  ObjectArchetype::ObjectArchetype(const std::string& name) :
    name_(name),
    componentArrays_()
  {
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