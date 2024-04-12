/* ======================================================================== */
/*!
 * \file            DeleteStartingObject.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Removes an starting object from its pool.
 */
 /* ======================================================================== */

#include "DeleteStartingObject.hpp"
#include <Editor.hpp>

namespace Barrage
{
  DeleteStartingObject::DeleteStartingObject(
    const std::string& sceneName, 
    const std::string& poolName, 
    const std::string& startingObjectName) :
    Command("Deleted object. (" + startingObjectName + ")"),
    sceneName_(sceneName),
    poolName_(poolName),
    startingObjectName_(startingObjectName),
    undoArchetype_()
  {
  }

  bool DeleteStartingObject::Execute()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);

    if (scene == nullptr || scene->poolArchetypes_.count(poolName_) == 0)
    {
      return false;
    }

    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    if (poolArchetype.startingObjects_.count(startingObjectName_) == 0)
    {
      return false;
    }

    undoArchetype_ = poolArchetype.startingObjects_.at(startingObjectName_);
    poolArchetype.startingObjects_.erase(startingObjectName_);

    if (Editor::Get().Data().selectedStartingObject_ == startingObjectName_)
    {
      Editor::Get().Data().selectedStartingObject_ = std::string();
    }

    return true;
  }

  void DeleteStartingObject::Undo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    poolArchetype.startingObjects_.emplace(startingObjectName_, undoArchetype_);
  }

  void DeleteStartingObject::Redo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);
    
    poolArchetype.startingObjects_.erase(startingObjectName_);
    
    if (Editor::Get().Data().selectedStartingObject_ == startingObjectName_)
    {
      Editor::Get().Data().selectedStartingObject_ = std::string();
    }
  }
}