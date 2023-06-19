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
#include <Editor.hpp>

namespace Barrage
{
  DeleteObject::DeleteObject(
    const std::string& sceneName, 
    const std::string& poolName, 
    const std::string& objectName) :
    Command("Deleted object. (" + objectName + ")"),
    sceneName_(sceneName),
    poolName_(poolName),
    objectName_(objectName),
    isStartingObject_(true),
    undoIndex_(0),
    undoArchetype_(nullptr)
  {
  }

  DeleteObject::~DeleteObject()
  {
    delete undoArchetype_;
  }

  bool DeleteObject::Execute()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    if (scene == nullptr)
    {
      return false;
    }

    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    if (poolArchetype == nullptr)
    {
      return false;
    }

    undoArchetype_ = poolArchetype->ExtractStartingObject(objectName_, &undoIndex_);

    if (undoArchetype_ == nullptr)
    {
      undoArchetype_ = poolArchetype->ExtractSpawnArchetype(objectName_, &undoIndex_);
      isStartingObject_ = false;
    }

    if (undoArchetype_ == nullptr)
    {
      return false;
    }

    if (Editor::Instance->Data().selectedObject_ == objectName_)
    {
      Editor::Instance->Data().selectedObject_ = std::string();
    }

    return true;
  }

  void DeleteObject::Undo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    if (isStartingObject_)
    {
      poolArchetype->AddStartingObject(undoArchetype_, &undoIndex_);
    }
    else
    {
      poolArchetype->AddSpawnArchetype(undoArchetype_, &undoIndex_);
    }
    
    undoArchetype_ = nullptr;
  }

  void DeleteObject::Redo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    if (isStartingObject_)
    {
      undoArchetype_ = poolArchetype->ExtractStartingObject(objectName_, &undoIndex_);
    }
    else
    {
      undoArchetype_ = poolArchetype->ExtractSpawnArchetype(objectName_, &undoIndex_);
    }

    if (Editor::Instance->Data().selectedObject_ == objectName_)
    {
      Editor::Instance->Data().selectedObject_ = std::string();
    }
  }
}