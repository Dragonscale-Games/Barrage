/* ======================================================================== */
/*!
 * \file            SpaceManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 

 */
/* ======================================================================== */

#include "stdafx.h"
#include "SpaceManager.hpp"

namespace Barrage
{
  SpaceManager::SpaceManager() :
    spaces_(),
    updateOrder_()
  {
  }

  SpaceManager::~SpaceManager()
  {
    for (auto it = spaces_.begin(); it != spaces_.end(); ++it)
    {
      delete it->second;
    }
  }

  void SpaceManager::AddSpace(const std::string name, const std::string scene)
  {
    if (spaces_.find(name) != spaces_.end())
      return;

    Space* new_space = new Space;

    new_space->SetScene(scene);

    spaces_[name] = new_space;
    updateOrder_.push_front(scene);
  }
}