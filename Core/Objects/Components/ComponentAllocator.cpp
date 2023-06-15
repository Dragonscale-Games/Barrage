/* ======================================================================== */
/*!
 * \file            ComponentAllocator.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Interface for allocating any type of component via its name.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "ComponentAllocator.hpp"
#include "Objects/Pools/Pool.hpp"

namespace Barrage
{
  ComponentAllocMap ComponentAllocator::componentAllocMap_ = ComponentAllocMap();
  ComponentArrayAllocMap ComponentAllocator::componentArrayAllocMap_ = ComponentArrayAllocMap();
  TagSet ComponentAllocator::tagSet_ = TagSet();

  std::vector<std::string_view> ComponentAllocator::componentNames_ = std::vector<std::string_view>();
  std::vector<std::string_view> ComponentAllocator::componentArrayNames_ = std::vector<std::string_view>();
  std::vector<std::string_view> ComponentAllocator::tagNames_ = std::vector<std::string_view>();

  bool ComponentAllocator::componentNamesSorted_ = false;
  bool ComponentAllocator::componentArrayNamesSorted_ = false;
  bool ComponentAllocator::tagNamesSorted_ = false;

  void ComponentAllocator::RegisterTag(const std::string_view& tag)
  {
    if (tagSet_.count(tag) == 0)
    {
      tagSet_.insert(tag);
      tagNames_.push_back(tag);
      tagNamesSorted_ = false;
    }
  }

  Component* ComponentAllocator::AllocateComponent(const std::string_view& name, Component* initializer)
  {
    if (componentAllocMap_.find(name) == componentAllocMap_.end())
    {
      return nullptr;
    }
    else
    {
      ComponentAllocFunc function = componentAllocMap_.at(name);
      return function(initializer);
    }
  }

  ComponentArray* ComponentAllocator::AllocateComponentArray(const std::string_view& name, unsigned capacity)
  {
    if (componentArrayAllocMap_.find(name) == componentArrayAllocMap_.end())
    {
      return nullptr;
    }
    else
    {
      ComponentArrayAllocFunc function = componentArrayAllocMap_.at(name);
      return function(capacity);
    }
  }

  std::string_view ComponentAllocator::GetComponentLiteral(const std::string_view& component)
  {
    auto iterator = componentAllocMap_.find(component);

    if (iterator != componentAllocMap_.end())
    {
      return iterator->first;
    }
    else
    {
      return std::string_view();
    }
  }

  std::string_view ComponentAllocator::GetComponentArrayLiteral(const std::string_view& componentArray)
  {
    auto iterator = componentArrayAllocMap_.find(componentArray);

    if (iterator != componentArrayAllocMap_.end())
    {
      return iterator->first;
    }
    else
    {
      return std::string_view();
    }
  }

  std::string_view ComponentAllocator::GetTagLiteral(const std::string_view& tag)
  {
    auto iterator = tagSet_.find(tag);
    
    if (iterator != tagSet_.end())
    {
      return *iterator;
    }
    else
    {
      return std::string_view();
    }
  }

  const std::vector<std::string_view>& ComponentAllocator::GetComponentNames()
  {
    if (!componentNamesSorted_)
    {
      std::sort(componentNames_.begin(), componentNames_.end());
      componentNamesSorted_ = true;
    }

    return componentNames_;
  }

  const std::vector<std::string_view>& ComponentAllocator::GetComponentArrayNames()
  {
    if (!componentArrayNamesSorted_)
    {
      std::sort(componentArrayNames_.begin(), componentArrayNames_.end());
      componentArrayNamesSorted_ = true;
    }

    return componentArrayNames_;
  }
  
  const std::vector<std::string_view>& ComponentAllocator::GetTagNames()
  {
    if (!tagNamesSorted_)
    {
      std::sort(tagNames_.begin(), tagNames_.end());
      tagNamesSorted_ = true;
    }

    return tagNames_;
  }
}