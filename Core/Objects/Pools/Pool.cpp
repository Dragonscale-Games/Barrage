/* ======================================================================== */
/*!
 * \file            Pool.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   An object pool is a block of memory that can hold a prespecified number
   of objects with a specific combination of components.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "Pool.hpp"

namespace Barrage
{
  Pool::Pool(const std::string& name, unsigned capacity) :
    components_(),
    componentArrays_(),
    tags_(),
    numActiveObjects_(0),
    numQueuedObjects_(0),
    capacity_(capacity),
    name_(name)
  {
  }

  Pool::Pool(const Pool& other) :
    components_(),
    componentArrays_(),
    tags_(other.tags_),
    numActiveObjects_(other.numActiveObjects_),
    numQueuedObjects_(other.numQueuedObjects_),
    capacity_(other.capacity_),
    name_(other.name_)
  {
    for (const auto& pair : other.components_)
    {
      components_[pair.first] = pair.second->Clone();
    }

    for (const auto& pair : other.componentArrays_)
    {
      componentArrays_[pair.first] = pair.second->Clone();
    }
  }

  Pool& Pool::operator=(const Pool& other)
  {
    tags_ = other.tags_;
    numActiveObjects_ = other.numActiveObjects_;
    numQueuedObjects_ = other.numQueuedObjects_;
    capacity_ = other.capacity_;
    name_ = other.name_;

    components_.clear();
    componentArrays_.clear();

    for (const auto& pair : other.components_)
    {
      components_[pair.first] = pair.second->Clone();
    }

    for (const auto& pair : other.componentArrays_)
    {
      componentArrays_[pair.first] = pair.second->Clone();
    }

    return *this;
  }
}