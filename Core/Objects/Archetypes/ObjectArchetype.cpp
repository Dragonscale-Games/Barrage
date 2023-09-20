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
#include "Objects/Components/ComponentFactory.hpp"

namespace Barrage
{
  ObjectArchetype::ObjectArchetype(const std::string& name, const std::vector<std::string>& componentArrayNames) :
    name_(name),
    componentArrays_()
  {
    for (const auto& componentArrayName : componentArrayNames)
    {
      std::shared_ptr<ComponentArray> componentArray = ComponentFactory::AllocateComponentArray(componentArrayName, 1);

      // TODO: Log/throw something if these conditions aren't met
      if (componentArray && componentArrays_.count(componentArrayName) == 0)
      {
        componentArrays_.emplace(componentArrayName, componentArray);
      }
    }
  }

  ObjectArchetype::ObjectArchetype(const ObjectArchetype& other) :
    name_(other.name_),
    componentArrays_()
  {
    for (const auto& pair : other.componentArrays_)
    {
      componentArrays_.emplace(pair.first, pair.second->Clone());
    }
  }

  ObjectArchetype& ObjectArchetype::operator=(const ObjectArchetype& other)
  {
    name_ = other.name_;
    componentArrays_.clear();
    
    for (const auto& pair : other.componentArrays_)
    {
      componentArrays_.emplace(pair.first, pair.second->Clone());
    }

    return *this;
  }
}