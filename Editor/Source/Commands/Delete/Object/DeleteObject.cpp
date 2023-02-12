/* ======================================================================== */
/*!
 * \file            DeleteObject.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Removes an object archetype from the scene and the archetype manager.
 */
 /* ======================================================================== */

#include "DeleteObject.hpp"
#include <Engine/Engine.hpp>
#include <Editor/Editor.hpp>

namespace Barrage
{
  DeleteObject::DeleteObject(
    const std::string& spaceName, 
    const std::string& sceneName, 
    const std::string& poolName, 
    const std::string& objectName) :
    Command("Deleted object. (" + objectName + ")"),
    spaceName_(spaceName),
    sceneName_(sceneName),
    poolName_(poolName),
    objectName_(objectName),
    objectIndex_(),
    removedArchetype_()
  {
  }

  bool DeleteObject::Execute()
  {
    Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    if (space == nullptr || scene == nullptr || !scene->HasObject(poolName_, objectName_))
    {
      return false;
    }

    PoolInfo* scenePool = scene->GetPoolInfo(poolName_);

    if (scenePool == nullptr)
    {
      return false;
    }

    ObjectManager& objectManager = space->GetObjectManager();
    removedArchetype_ = objectManager.ExtractObjectArchetype(objectName_);

    if (removedArchetype_ == nullptr)
    {
      return false;
    }

    scene->RemoveObject(poolName_, objectName_, &objectIndex_);

    if (Editor::Instance->Data().selectedObject_ == objectName_)
    {
      Editor::Instance->Data().selectedObject_ = std::string();
    }

    return true;
  }

  void DeleteObject::Undo()
  {
    Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    ObjectManager& objectManager = space->GetObjectManager();

    objectManager.AddObjectArchetype(objectName_, removedArchetype_);
    scene->AddObject(poolName_, objectName_, &objectIndex_);
  }

  void DeleteObject::Redo()
  {
    Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    ObjectManager& objectManager = space->GetObjectManager();

    removedArchetype_ = objectManager.ExtractObjectArchetype(objectName_);
    scene->RemoveObject(poolName_, objectName_, &objectIndex_);

    if (Editor::Instance->Data().selectedObject_ == objectName_)
    {
      Editor::Instance->Data().selectedObject_ = std::string();
    }
  }
}