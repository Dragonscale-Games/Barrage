/* ======================================================================== */
/*!
 * \file            DuplicatePool.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Duplicates an existing pool archetype in the scene.
 */
 /* ======================================================================== */

#include "DuplicatePool.hpp"
#include "Editor.hpp"

namespace Barrage
{
  DuplicatePool::DuplicatePool(const std::string& sceneName, const std::string& poolName) :
    Command("New pool created."),
    sceneName_(sceneName),
    poolName_(poolName),
    newPool_()
  {
  }

  bool DuplicatePool::Execute()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);

    if (scene == nullptr || scene->poolArchetypes_.count(poolName_) == 0)
    {
      return false;
    }

    newPool_ = scene->poolArchetypes_.at(poolName_);

    unsigned counter = 2;

    do {
      poolName_ = newPool_.name_ + " " + std::to_string(counter);
      counter++;

    } while (scene->poolArchetypes_.count(poolName_));

    newPool_.name_ = poolName_;

    scene->poolArchetypes_.emplace(poolName_, newPool_);

    return true;
  }

  void DuplicatePool::Undo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);

    scene->poolArchetypes_.erase(poolName_);

    if (Editor::Get().Data().selectedPool_ == poolName_)
    {
      Editor::Get().Data().selectedPool_ = std::string();
    }
  }

  void DuplicatePool::Redo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);

    scene->poolArchetypes_.emplace(poolName_, newPool_);
  }
}