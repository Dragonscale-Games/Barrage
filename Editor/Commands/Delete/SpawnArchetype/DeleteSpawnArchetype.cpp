/* ======================================================================== */
/*!
 * \file            DeleteSpawnArchetype.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Removes a spawn archetype from its pool.
 */
 /* ======================================================================== */

#include "DeleteSpawnArchetype.hpp"
#include <Editor.hpp>

namespace Barrage
{
  DeleteSpawnArchetype::DeleteSpawnArchetype(
    const std::string& sceneName,
    const std::string& poolName,
    const std::string& spawnArchetypeName) :
    Command("Deleted spawn archetype. (" + spawnArchetypeName + ")"),
    sceneName_(sceneName),
    poolName_(poolName),
    spawnArchetypeName_(spawnArchetypeName),
    undoArchetype_()
  {
  }

  bool DeleteSpawnArchetype::Execute()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);

    if (scene == nullptr || scene->poolArchetypes_.count(poolName_) == 0)
    {
      return false;
    }

    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    if (poolArchetype.spawnArchetypes_.count(spawnArchetypeName_) == 0)
    {
      return false;
    }

    undoArchetype_ = poolArchetype.spawnArchetypes_.at(spawnArchetypeName_);
    poolArchetype.spawnArchetypes_.erase(spawnArchetypeName_);

    if (Editor::Get().Data().selectedSpawnArchetype_ == spawnArchetypeName_)
    {
      Editor::Get().Data().selectedSpawnArchetype_ = std::string();
    }

    return true;
  }

  void DeleteSpawnArchetype::Undo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    poolArchetype.spawnArchetypes_.emplace(spawnArchetypeName_, undoArchetype_);
  }

  void DeleteSpawnArchetype::Redo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    poolArchetype.spawnArchetypes_.erase(spawnArchetypeName_);

    if (Editor::Get().Data().selectedSpawnArchetype_ == spawnArchetypeName_)
    {
      Editor::Get().Data().selectedSpawnArchetype_ = std::string();
    }
  }
}