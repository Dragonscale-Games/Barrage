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

  void SceneManager::AddScene(Scene* scene)
  {
    if (scene == nullptr)
    {
      return;
    }
    
    std::string sceneName = scene->GetName();

    if (scenes_.count(sceneName))
    {
      delete scenes_.at(sceneName);
    }

    scenes_[sceneName] = scene;
  }

  Scene* SceneManager::GetScene(const std::string& name)
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

  bool SceneManager::RenameScene(const std::string& sceneName, const std::string& newName)
  {
    if (scenes_.count(sceneName) == 0 || scenes_.count(newName))
    {
      return false;
    }

    Scene* scene = scenes_.at(sceneName);

    scene->SetName(newName);

    scenes_.erase(sceneName);
    scenes_[newName] = scene;

    return true;
  }
}