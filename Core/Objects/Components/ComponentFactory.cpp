/* ======================================================================== */
/*!
 * \file            ComponentFactory.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Interface for allocating any type of component via its name.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "ComponentFactory.hpp"
#include "Objects/Pools/Pool.hpp"

namespace Barrage
{
  ComponentFactoryMethodMap ComponentFactory::componentFactoryMethodMap_ = ComponentFactoryMethodMap();           
  ComponentArrayFactoryMethodMap ComponentFactory::componentArrayFactoryMethodMap_ = ComponentArrayFactoryMethodMap();

  StringSet ComponentFactory::componentNames_ = StringSet();
  StringSet ComponentFactory::componentArrayNames_ = StringSet();
  StringSet ComponentFactory::tagNames_ = StringSet();

  void ComponentFactory::RegisterTag(const std::string& tag)
  {
    tagNames_.insert(tag);
  }

  ComponentDeepPtr ComponentFactory::AllocateComponent(const std::string& name, ComponentDeepPtr initializer)
  {
    if (componentFactoryMethodMap_.count(name))
    {
      ComponentFactoryMethod function = componentFactoryMethodMap_.at(name);
      return function(initializer);
    }
    else
    {
      return nullptr;
    }
  }

  ComponentArrayDeepPtr ComponentFactory::AllocateComponentArray(const std::string& name, unsigned capacity)
  {
    if (componentArrayFactoryMethodMap_.count(name))
    {
      ComponentArrayFactoryMethod function = componentArrayFactoryMethodMap_.at(name);
      return function(capacity);
    }
    else
    {
      return nullptr;
    }
  }

  const StringSet& ComponentFactory::GetComponentNames()
  {
    return componentNames_;
  }

  const StringSet& ComponentFactory::GetComponentArrayNames()
  {
    return componentArrayNames_;
  }

  const StringSet& ComponentFactory::GetTagNames()
  {
    return tagNames_;
  }
}