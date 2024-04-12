/* ======================================================================== */
/*!
 * \file            RenamePool.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Renames a pool.
 */
 /* ======================================================================== */

#include "RenamePool.hpp"
#include <Editor.hpp>

namespace Barrage
{
  RenamePool::RenamePool(
    const std::string& sceneName,
    const std::string& poolName,
    const std::string& newName) :
    Command("Renamed pool \"" + poolName + "\" to \"" + newName + "\"."),
    sceneName_(sceneName),
    poolName_(poolName),
    newName_(newName)
  {
  }

  bool RenamePool::Execute()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);

    if (scene == nullptr || scene->poolArchetypes_.count(poolName_) == 0)
    {
      return false;
    }

    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);
    
    if (scene->poolArchetypes_.count(newName_))
    {
      return false;
    }
    
    poolArchetype.name_ = newName_;
    scene->poolArchetypes_.emplace(newName_, poolArchetype);
    scene->poolArchetypes_.erase(poolName_);
    
    EditorData& editorData = Editor::Get().Data();
    if (editorData.selectedPool_ == poolName_)
    {
      editorData.selectedPool_ = newName_;
    }

    return true;
  }

  void RenamePool::Undo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(newName_);

    poolArchetype.name_ = poolName_;
    scene->poolArchetypes_.emplace(poolName_, poolArchetype);
    scene->poolArchetypes_.erase(newName_);

    EditorData& editorData = Editor::Get().Data();
    if (editorData.selectedPool_ == newName_)
    {
      editorData.selectedPool_ = poolName_;
    }
  }

  void RenamePool::Redo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    poolArchetype.name_ = newName_;
    scene->poolArchetypes_.emplace(newName_, poolArchetype);
    scene->poolArchetypes_.erase(poolName_);

    EditorData& editorData = Editor::Get().Data();
    if (editorData.selectedPool_ == poolName_)
    {
      editorData.selectedPool_ = newName_;
    }
  }
}