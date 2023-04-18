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

namespace Barrage
{
  ComponentArrayAllocMap ComponentAllocator::componentArrayAllocMap_ = ComponentArrayAllocMap();
  SharedComponentAllocMap ComponentAllocator::sharedComponentAllocMap_ = SharedComponentAllocMap();
  TagSet ComponentAllocator::tagSet_ = TagSet();

  std::vector<std::string_view> ComponentAllocator::componentArrayNames_ = std::vector<std::string_view>();
  std::vector<std::string_view> ComponentAllocator::sharedComponentNames_ = std::vector<std::string_view>();
  std::vector<std::string_view> ComponentAllocator::tagNames_ = std::vector<std::string_view>();

  bool ComponentAllocator::componentArrayNamesSorted_ = false;
  bool ComponentAllocator::sharedComponentNamesSorted_ = false;
  bool ComponentAllocator::tagNamesSorted_ = false;

  void ComponentAllocator::RegisterTag(const std::string_view& tag)
  {
    tagSet_.insert(tag);
    tagNamesSorted_ = false;
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

  SharedComponent* ComponentAllocator::AllocateSharedComponent(const std::string_view& name, SharedComponent* initializer)
  {
    if (sharedComponentAllocMap_.find(name) == sharedComponentAllocMap_.end())
    {
      return nullptr;
    }
    else
    {
      SharedComponentAllocFunc function = sharedComponentAllocMap_.at(name);
      return function(initializer);
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

  std::string_view ComponentAllocator::GetSharedComponentLiteral(const std::string_view& sharedComponent)
  {
    auto iterator = sharedComponentAllocMap_.find(sharedComponent);

    if (iterator != sharedComponentAllocMap_.end())
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

  const std::vector<std::string_view>& ComponentAllocator::GetComponentArrayNames()
  {
    if (!componentArrayNamesSorted_)
    {
      std::sort(componentArrayNames_.begin(), componentArrayNames_.end());
      componentArrayNamesSorted_ = true;
    }
    
    return componentArrayNames_;
  }

  const std::vector<std::string_view>& ComponentAllocator::GetSharedComponentNames()
  {
    if (!sharedComponentNamesSorted_)
    {
      std::sort(sharedComponentNames_.begin(), sharedComponentNames_.end());
      sharedComponentNamesSorted_ = true;
    }
    
    return sharedComponentNames_;
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