/* ======================================================================== */
/*!
 * \file            RenameSpawnArchetype.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Renames a spawn archetype in a pool.
 */
 /* ======================================================================== */

#include "RenameSpawnArchetype.hpp"
#include <Editor.hpp>

namespace Barrage
{
  RenameSpawnArchetype::RenameSpawnArchetype(
    const std::string& sceneName,
    const std::string& poolName,
    const std::string& spawnArchetypeName,
    const std::string& newName) :
    Command("Renamed spawn archetype \"" + spawnArchetypeName + "\" to \"" + newName + "\"."),
    sceneName_(sceneName),
    poolName_(poolName),
    spawnArchetypeName_(spawnArchetypeName),
    newName_(newName)
  {
  }

  bool RenameSpawnArchetype::Execute()
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

    if (poolArchetype.spawnArchetypes_.count(newName_))
    {
      return false;
    }

    ObjectArchetype& objectArchetype = poolArchetype.spawnArchetypes_.at(spawnArchetypeName_);

    objectArchetype.name_ = newName_;
    poolArchetype.spawnArchetypes_.emplace(newName_, objectArchetype);
    poolArchetype.spawnArchetypes_.erase(spawnArchetypeName_);

    EditorData& editorData = Editor::Get().Data();
    if (editorData.selectedSpawnArchetype_ == spawnArchetypeName_)
    {
      editorData.selectedSpawnArchetype_ = newName_;
    }

    return true;
  }

  void RenameSpawnArchetype::Undo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);
    ObjectArchetype& objectArchetype = poolArchetype.spawnArchetypes_.at(newName_);

    objectArchetype.name_ = spawnArchetypeName_;
    poolArchetype.spawnArchetypes_.emplace(spawnArchetypeName_, objectArchetype);
    poolArchetype.spawnArchetypes_.erase(newName_);

    EditorData& editorData = Editor::Get().Data();
    if (editorData.selectedSpawnArchetype_ == newName_)
    {
      editorData.selectedSpawnArchetype_ = spawnArchetypeName_;
    }
  }

  void RenameSpawnArchetype::Redo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);
    ObjectArchetype& objectArchetype = poolArchetype.spawnArchetypes_.at(spawnArchetypeName_);

    objectArchetype.name_ = newName_;
    poolArchetype.spawnArchetypes_.emplace(newName_, objectArchetype);
    poolArchetype.spawnArchetypes_.erase(spawnArchetypeName_);

    EditorData& editorData = Editor::Get().Data();
    if (editorData.selectedSpawnArchetype_ == spawnArchetypeName_)
    {
      editorData.selectedSpawnArchetype_ = newName_;
    }
  }
}