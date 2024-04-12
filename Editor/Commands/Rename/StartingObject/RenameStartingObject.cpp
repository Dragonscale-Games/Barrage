/* ======================================================================== */
/*!
 * \file            RenameStartingObject.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Renames a starting object in a pool.
 */
 /* ======================================================================== */

#include "RenameStartingObject.hpp"
#include <Editor.hpp>

namespace Barrage
{
  RenameStartingObject::RenameStartingObject(
    const std::string& sceneName,
    const std::string& poolName,
    const std::string& startingObjectName,
    const std::string& newName) :
    Command("Renamed starting object \"" + startingObjectName + "\" to \"" + newName + "\"."),
    sceneName_(sceneName),
    poolName_(poolName),
    startingObjectName_(startingObjectName),
    newName_(newName)
  {
  }
  
  bool RenameStartingObject::Execute()
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

    if (poolArchetype.startingObjects_.count(newName_))
    {
      return false;
    }

    ObjectArchetype& objectArchetype = poolArchetype.startingObjects_.at(startingObjectName_);

    objectArchetype.name_ = newName_;
    poolArchetype.startingObjects_.emplace(newName_, objectArchetype);
    poolArchetype.startingObjects_.erase(startingObjectName_);

    EditorData& editorData = Editor::Get().Data();
    if (editorData.selectedStartingObject_ == startingObjectName_)
    {
      editorData.selectedStartingObject_ = newName_;
    }

    return true;
  }
    
  void RenameStartingObject::Undo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);
    ObjectArchetype& objectArchetype = poolArchetype.startingObjects_.at(newName_);

    objectArchetype.name_ = startingObjectName_;
    poolArchetype.startingObjects_.emplace(startingObjectName_, objectArchetype);
    poolArchetype.startingObjects_.erase(newName_);

    EditorData& editorData = Editor::Get().Data();
    if (editorData.selectedStartingObject_ == newName_)
    {
      editorData.selectedStartingObject_ = startingObjectName_;
    }
  }

  void RenameStartingObject::Redo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);
    ObjectArchetype& objectArchetype = poolArchetype.startingObjects_.at(startingObjectName_);

    objectArchetype.name_ = newName_;
    poolArchetype.startingObjects_.emplace(newName_, objectArchetype);
    poolArchetype.startingObjects_.erase(startingObjectName_);

    EditorData& editorData = Editor::Get().Data();
    if (editorData.selectedStartingObject_ == startingObjectName_)
    {
      editorData.selectedStartingObject_ = newName_;
    }
  }
}