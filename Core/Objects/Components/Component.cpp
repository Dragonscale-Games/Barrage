/* ======================================================================== */
/*!
 * \file            Component.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base component class that all components should inherit from.
 */
 /* ======================================================================== */

#include "Component.hpp"

namespace Barrage
{
  ComponentMap::ComponentMap() :
    data_()
  {
  }

  ComponentMap::ComponentMap(const ComponentMap& other) :
    data_()
  {
    for (const auto& pair : other.data_)
    {
      data_.emplace(pair.first, pair.second->Clone());
    }
  }

  ComponentMap& ComponentMap::operator=(const ComponentMap& other)
  {
    data_.clear();

    for (const auto& pair : other.data_)
    {
      data_.emplace(pair.first, pair.second->Clone());
    }

    return *this;
  }

  std::map<std::string, std::shared_ptr<Component>>& ComponentMap::Data()
  {
    return data_;
  }
}