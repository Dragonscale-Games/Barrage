/* ======================================================================== */
/*!
 * \file            CreateTag.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Adds a tag to a pool archetype.
 */
 /* ======================================================================== */

#include "CreateTag.hpp"
#include <Editor.hpp>

namespace Barrage
{
  CreateTag::CreateTag(
    const std::string& sceneName,
    const std::string& poolName,
    const std::string& tag) :
    Command("Added \"" + tag + "\" tag to " + poolName + "."),
    sceneName_(sceneName),
    poolName_(poolName),
    tag_(tag)
  {
  }

  bool CreateTag::Execute()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);

    if (scene == nullptr || scene->poolArchetypes_.count(poolName_) == 0)
    {
      return false;
    }

    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    if (poolArchetype.tags_.count(tag_))
    {
      return false;
    }

    poolArchetype.tags_.insert(tag_);

    return true;
  }
  
  void CreateTag::Undo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    poolArchetype.tags_.erase(tag_);
  }
  
  void CreateTag::Redo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    poolArchetype.tags_.insert(tag_);
  }
}