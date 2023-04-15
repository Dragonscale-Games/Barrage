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
#include <Engine/Engine.hpp>
#include <Editor/Editor.hpp>

namespace Barrage
{
  DeletePool::DeletePool(
    const std::string& spaceName,
    const std::string& sceneName,
    const std::string& poolName) :
    Command("Deleted pool. (" + poolName + ")"),
    spaceName_(spaceName),
    sceneName_(sceneName),
    poolName_(poolName),
    undoSceneIndex_(),
    //undoScenePool_(poolName_),
    undoPoolArchetype_()
    //undoObjectArchetypes_()
  {
  }

  DeletePool::~DeletePool()
  {
    delete undoPoolArchetype_;
    
    /*for (auto it = undoObjectArchetypes_.begin(); it != undoObjectArchetypes_.end(); ++it)
    {
      delete it->second;
    }*/
  }

  bool DeletePool::Execute()
  {
    //Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    //Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    //if (space == nullptr || scene == nullptr)
    //{
    //  return false;
    //}
    //
    //ObjectManager& objectManager = space->GetObjectManager();
    //PoolInfo* scenePool = scene->GetPoolInfo(poolName_);

    //if (scenePool == nullptr)
    //{
    //  return false;
    //}

    //undoScenePool_ = *scenePool;
    //undoPoolArchetype_ = objectManager.ExtractPoolArchetype(poolName_);

    //if (undoPoolArchetype_ == nullptr)
    //{
    //  return false;
    //}

    //for (auto it = scenePool->objects_.begin(); it != scenePool->objects_.end(); ++it)
    //{
    //  std::string& objectName = *it;
    //  ObjectArchetype* objectArchetype = objectManager.ExtractObjectArchetype(objectName);

    //  // this should never happen
    //  if (objectArchetype == nullptr)
    //  {
    //    LogWidget::AddEntry("FATAL ERROR: An object archetype in the deleted pool did not exist.");
    //    return false;
    //  }

    //  undoObjectArchetypes_[objectName] = objectArchetype;

    //  if (Editor::Instance->Data().selectedObject_ == objectName)
    //  {
    //    Editor::Instance->Data().selectedObject_ = std::string();
    //  }
    //}

    //scene->RemovePool(poolName_, &undoSceneIndex_);

    //if (Editor::Instance->Data().selectedPool_ == poolName_)
    //{
    //  Editor::Instance->Data().selectedPool_ = std::string();
    //}

    return true;
  }

  void DeletePool::Undo()
  {
    /*Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    ObjectManager& objectManager = space->GetObjectManager();

    scene->AddStartingPool(undoScenePool_, &undoSceneIndex_);
    objectManager.AddPoolArchetype(poolName_, undoPoolArchetype_);
    undoPoolArchetype_ = nullptr;

    for (auto it = undoObjectArchetypes_.begin(); it != undoObjectArchetypes_.end(); ++it)
    {
      objectManager.AddObjectArchetype(it->first, it->second);
    }
    undoObjectArchetypes_.clear();*/
  }

  void DeletePool::Redo()
  {
    /*Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    ObjectManager& objectManager = space->GetObjectManager();

    scene->RemovePool(poolName_, &undoSceneIndex_);
    undoPoolArchetype_ = objectManager.ExtractPoolArchetype(poolName_);

    for (auto it = undoScenePool_.objects_.begin(); it != undoScenePool_.objects_.end(); ++it)
    {
      std::string& objectName = *it;
      ObjectArchetype* objectArchetype = objectManager.ExtractObjectArchetype(objectName);
      undoObjectArchetypes_[objectName] = objectArchetype;

      if (Editor::Instance->Data().selectedObject_ == objectName)
      {
        Editor::Instance->Data().selectedObject_ = std::string();
      }
    }

    if (Editor::Instance->Data().selectedPool_ == poolName_)
    {
      Editor::Instance->Data().selectedPool_ = std::string();
    }*/
  }
}