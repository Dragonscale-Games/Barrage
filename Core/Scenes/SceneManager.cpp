/* ======================================================================== */
/*!
 * \file            SceneManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Manages all game scenes.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "SceneManager.hpp"

namespace Barrage
{
  SceneManager::SceneManager() :
    scenes_()
  {
  }

  void SceneManager::AddScene(const std::string& name, Scene&& scene)
  {
    scenes_.emplace(name, std::move(scene));
  }

  Scene* SceneManager::GetScene(const std::string& name)
  {
    if (scenes_.count(name))
    {
      return &scenes_.at(name);
    }
    else
    {
      return nullptr;
    }
  }
}