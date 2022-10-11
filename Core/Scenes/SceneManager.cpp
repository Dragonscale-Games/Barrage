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

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>

#include <fstream>
#include <filesystem>

namespace Barrage
{
  SceneManager::SceneManager() :
    scenes_()
  {
  }

  SceneManager::~SceneManager()
  {
    for (auto it = scenes_.begin(); it != scenes_.end(); ++it)
    {
      delete it->second;
    }
  }

  void SceneManager::AddScene(const std::string name, Scene* scene)
  {
    if (scenes_.find(name) == scenes_.end())
    {
      scenes_[name] = scene;
    }
    else
    {
      delete scene;
    }
  }

  Scene* SceneManager::GetScene(const std::string name)
  {
    if (scenes_.find(name) == scenes_.end())
    {
      return nullptr;
    }
    else
    {
      return scenes_.at(name);
    }
  }

  std::vector<std::string> SceneManager::GetSceneNames()
  {
    std::vector<std::string> scene_names;

    for (auto it = scenes_.begin(); it != scenes_.end(); ++it)
    {
      scene_names.push_back(it->first);
    }

    return scene_names;
  }
}