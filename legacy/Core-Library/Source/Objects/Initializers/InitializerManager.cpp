/* ======================================================================== */
/*!
 * \file            InitializerManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Keeps track of object initialization functions and their names.
 */
/* ======================================================================== */

#include "stdafx.h"
#include "InitializerManager.hpp"

namespace Barrage
{
  InitializerManager::InitializerManager() :
    initializers_(),
    initializerNames_()
  {
  }

  void InitializerManager::RegisterInitializer(const std::string name, Initializer initializer)
  {
    if (initializers_.find(name) != initializers_.end())
    {
      return;
    }

    if (initializer == nullptr)
    {
      return;
    }

    initializers_[name] = initializer;
    initializerNames_.push_back(name);
  }

  Initializer InitializerManager::GetInitializer(const std::string name)
  {
    if (initializers_.find(name) != initializers_.end())
    {
      return initializers_.at(name);
    }
    else
    {
      return nullptr;
    }
  }

  InitializerList InitializerManager::GetInitializerNames()
  {
    return initializerNames_;
  }
}