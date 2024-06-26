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
  ObjectArchetype::ObjectArchetype() :
    name_("Unnamed"),
    componentArrays_()
  {
  }
  
  ObjectArchetype::ObjectArchetype(const std::string& name, const StringSet& componentArrayNames) :
    name_(name),
    componentArrays_()
  {
    for (const auto& componentArrayName : componentArrayNames)
    {
      DeepPtr<ComponentArray> componentArray = ComponentFactory::AllocateComponentArray(componentArrayName, 1);

      // TODO: Log/throw something if these conditions aren't met
      if (componentArray && componentArrays_.count(componentArrayName) == 0)
      {
        componentArrays_.emplace(componentArrayName, componentArray);
      }
    }
  }
}