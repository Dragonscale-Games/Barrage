/* ======================================================================== */
/*!
 * \file            CreateSpawnArchetype.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Creates a new object archetype and adds it as a spawn archetype to a pool
   in the scene.
 */
 /* ======================================================================== */

#include "CreateSpawnArchetype.hpp"
#include "Editor.hpp"

namespace Barrage
{
  CreateSpawnArchetype::CreateSpawnArchetype(
    const std::string& sceneName,
    const std::string& poolName) :
    Command("New spawn archetype created in " + poolName + "."),
    sceneName_(sceneName),
    poolName_(poolName),
    spawnArchetypeName_()
  {
  }

  bool CreateSpawnArchetype::Execute()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);

    if (scene == nullptr || scene->poolArchetypes_.count(poolName_) == 0)
    {
      return false;
    }

    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    unsigned counter = 0;

    do {
      spawnArchetypeName_ = "Spawn Archetype";

      if (counter)
      {
        spawnArchetypeName_ += " ";
        spawnArchetypeName_ += std::to_string(counter);
      }

      counter++;

    } while (poolArchetype.spawnArchetypes_.count(spawnArchetypeName_));

    poolArchetype.spawnArchetypes_.emplace(spawnArchetypeName_, ObjectArchetype(spawnArchetypeName_, poolArchetype.componentArrayNames_));

    return true;
  }

  void CreateSpawnArchetype::Undo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    poolArchetype.spawnArchetypes_.erase(spawnArchetypeName_);

    if (Editor::Get().Data().selectedSpawnArchetype_ == spawnArchetypeName_)
    {
      Editor::Get().Data().selectedSpawnArchetype_ = std::string();
    }
  }

  void CreateSpawnArchetype::Redo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    poolArchetype.spawnArchetypes_.emplace(spawnArchetypeName_, ObjectArchetype(spawnArchetypeName_, poolArchetype.componentArrayNames_));
  }
}