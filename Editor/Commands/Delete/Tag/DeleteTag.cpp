/* ======================================================================== */
/*!
 * \file            DeleteTag.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Removes a tag from a pool archetype.
 */
 /* ======================================================================== */

#include "DeleteTag.hpp"
#include <Editor.hpp>

namespace Barrage
{
  DeleteTag::DeleteTag(
    const std::string& sceneName,
    const std::string& poolName,
    const std::string& tag) :
    Command("Removed \"" + tag + "\" tag from " + poolName + "."),
    sceneName_(sceneName),
    poolName_(poolName),
    tag_(tag)
  {
  }

  bool DeleteTag::Execute()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);

    if (scene == nullptr || scene->poolArchetypes_.count(poolName_) == 0)
    {
      return false;
    }

    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    if (poolArchetype.tags_.count(tag_) == 0)
    {
      return false;
    }

    poolArchetype.tags_.erase(tag_);

    return true;
  }

  void DeleteTag::Undo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    poolArchetype.tags_.insert(tag_);
  }

  void DeleteTag::Redo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    poolArchetype.tags_.erase(tag_);
  }
}
