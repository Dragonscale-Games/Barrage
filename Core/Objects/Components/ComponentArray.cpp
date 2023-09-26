/* ======================================================================== */
/*!
 * \file            ComponentArray.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base component array class that all component arrays should inherit from.
   Component arrays are used when each object in a pool needs its own copy
   of a component.
   For instance, each object may need its own position component.
 */
 /* ======================================================================== */

#include "ComponentArray.hpp"

namespace Barrage
{
  ComponentArrayMap::ComponentArrayMap() :
    data_()
  {
  }

  ComponentArrayMap::ComponentArrayMap(const ComponentArrayMap& other) :
    data_()
  {
    for (const auto& pair : other.data_)
    {
      data_.emplace(pair.first, pair.second->Clone());
    }
  }

  ComponentArrayMap& ComponentArrayMap::operator=(const ComponentArrayMap& other)
  {
    data_.clear();

    for (const auto& pair : other.data_)
    {
      data_.emplace(pair.first, pair.second->Clone());
    }

    return *this;
  }

  std::map<std::string, std::shared_ptr<ComponentArray>>& ComponentArrayMap::Data()
  {
    return data_;
  }
}