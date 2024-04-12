/* ======================================================================== */
/*!
 * \file            DeletePool.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Removes a pool archetype from the scene and the archetype manager.
 */
 /* ======================================================================== */

#include "DeletePool.hpp"
#include <Editor.hpp>

namespace Barrage
{
  DeletePool::DeletePool(const std::string& sceneName, const std::string& poolName) :
    Command("Deleted pool. (" + poolName + ")"),
    sceneName_(sceneName),
    poolName_(poolName),
    undoPoolArchetype_()
  {
  }

  bool DeletePool::Execute()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);

    if (scene == nullptr || scene->poolArchetypes_.count(poolName_) == 0)
    {
      return false;
    }

    undoPoolArchetype_ = scene->poolArchetypes_.at(poolName_);
    scene->poolArchetypes_.erase(poolName_);

    if (Editor::Get().Data().selectedPool_ == poolName_)
    {
      Editor::Get().Data().selectedPool_ = std::string();
    }

    return true;
  }

  void DeletePool::Undo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);

    scene->poolArchetypes_.emplace(poolName_, undoPoolArchetype_);
  }

  void DeletePool::Redo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);

    scene->poolArchetypes_.erase(poolName_);

    if (Editor::Get().Data().selectedPool_ == poolName_)
    {
      Editor::Get().Data().selectedPool_ = std::string();
    }
  }
}