/* ======================================================================== */
/*!
 * \file            CreatePool.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Creates a new (empty) pool archetype and adds that archetype to the scene.
 */
 /* ======================================================================== */

#include "CreatePool.hpp"
#include "Editor.hpp"

namespace Barrage
{
  CreatePool::CreatePool(const std::string& sceneName) :
    Command("New pool created."),
    sceneName_(sceneName),
    poolName_()
  {
  }

  bool CreatePool::Execute()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);

    if (scene == nullptr)
    {
      return false;
    }

    unsigned counter = 0;

    do {
      poolName_ = "Pool";

      if (counter)
      {
        poolName_ += " ";
        poolName_ += std::to_string(counter);
      }

      counter++;

    } while (scene->poolArchetypes_.count(poolName_));

    scene->poolArchetypes_.emplace(poolName_, PoolArchetype(poolName_, 1));

    return true;
  }

  void CreatePool::Undo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    scene->poolArchetypes_.erase(poolName_);

    if (Editor::Get().Data().selectedPool_ == poolName_)
    {
      Editor::Get().Data().selectedPool_ = std::string();
    }
  }

  void CreatePool::Redo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    scene->poolArchetypes_.emplace(poolName_, PoolArchetype(poolName_, 1));
  }
}