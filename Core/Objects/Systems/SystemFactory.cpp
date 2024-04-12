/* ======================================================================== */
/*!
 * \file            SystemFactory.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Interface for allocating any type of system via its name.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "SystemFactory.hpp"

namespace Barrage
{
  SystemFactoryMethodMap SystemFactory::systemFactoryMethodMap_ = SystemFactoryMethodMap();
  StringSet SystemFactory::systemNames_ = StringSet();

  std::shared_ptr<System> SystemFactory::CreateSystem(const std::string& name, Space& space)
  {
    if (systemFactoryMethodMap_.count(name))
    {
      SystemFactoryMethod function = systemFactoryMethodMap_.at(name);
      return function(space);
    }
    else
    {
      return nullptr;
    }
  }

  const StringSet& SystemFactory::GetSystemNames()
  {
    return systemNames_;
  }
}
