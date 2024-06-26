/* ======================================================================== */
/*!
 * \file            SpaceManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Manages all game spaces.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "SpaceManager.hpp"
#include "Engine.hpp"

namespace Barrage
{
  SpaceManager::SpaceManager() :
    spaces_()
  {
  }

  void SpaceManager::Update()
  {
    for (auto it = updateOrder_.begin(); it != updateOrder_.end(); ++it)
    {
      spaces_.at(*it).Update();
    }

    Engine::Get().Input().Reset();
  }

  void SpaceManager::Draw()
  {
    for (auto it = updateOrder_.rbegin(); it != updateOrder_.rend(); ++it)
    {
      spaces_.at(*it).Draw();
    }
  }

  void SpaceManager::AddSpace(const std::string& name)
  {
    if (spaces_.find(name) == spaces_.end())
    {
      spaces_[name];
      updateOrder_.push_front(name);
    }
  }

  Space* SpaceManager::GetSpace(const std::string& name)
  {
    if (spaces_.count(name))
    {
      return &spaces_.at(name);
    }
    else
    {
      return nullptr;
    }
  }

  void SpaceManager::SetSpacePaused(const std::string& name, bool isPaused)
  {
    if (spaces_.find(name) != spaces_.end())
    {
      spaces_.at(name).SetPaused(isPaused);
    }
  }
}