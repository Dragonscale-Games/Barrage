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

  void SpaceManager::Update()
  {
    for (auto it = updateOrder_.begin(); it != updateOrder_.end(); ++it)
    {
      spaces_[*it]->Update();
    }
  }

  void SpaceManager::Draw()
  {
    for (auto it = updateOrder_.rbegin(); it != updateOrder_.rend(); ++it)
    {
      spaces_[*it]->Draw();
    }
  }

  void SpaceManager::AddSpace(const std::string& name, Space* space)
  {
    if (spaces_.find(name) == spaces_.end())
    {
      spaces_[name] = space;
      updateOrder_.push_front(name);
    }
    else
    {
      delete space;
    }
  }

  void SpaceManager::SetSpacePaused(const std::string& name, bool isPaused)
  {
    if (spaces_.find(name) != spaces_.end())
    {
      spaces_[name]->SetPaused(isPaused);
    }
  }
}