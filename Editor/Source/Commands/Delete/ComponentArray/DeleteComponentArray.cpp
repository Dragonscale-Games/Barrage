/* ======================================================================== */
/*!
 * \file            DeleteComponentArray.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Removes a component array from a pool and removes the corresponding
    component from all objects in that pool.
 */
 /* ======================================================================== */

#include "DeleteComponentArray.hpp"
#include <Editor/Editor.hpp>

namespace Barrage
{
  DeleteComponentArray::DeleteComponentArray(
    const std::string& spaceName,
    const std::string& sceneName,
    const std::string& poolName,
    const std::string_view& componentArrayName) :
    Command("Removed " + std::string(componentArrayName) + " from " + poolName + "."),
    spaceName_(spaceName),
    sceneName_(sceneName),
    poolName_(poolName),
    undoIndex_(),
    componentArrayName_(componentArrayName)
  {
  }

  DeleteComponentArray::~DeleteComponentArray()
  {
    
  }

  bool DeleteComponentArray::Execute()
  {
    /*Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    if (space == nullptr || scene == nullptr || !scene->HasPool(poolName_))
    {
      return false;
    }

    ObjectManager& objectManager = space->GetObjectManager();
    PoolArchetype* poolArchetype = objectManager.GetPoolArchetype(poolName_);
    PoolInfo* scenePool = scene->GetPoolInfo(poolName_);

    if (poolArchetype == nullptr || scenePool == nullptr || !poolArchetype->HasComponentArray(componentArrayName_))
    {
      return false;
    }

    for (auto it = scenePool->objects_.begin(); it != scenePool->objects_.end(); ++it)
    {
      ObjectArchetype* objectArchetype = objectManager.GetObjectArchetype(*it);
      
      if (objectArchetype == nullptr || !objectArchetype->components_.count(componentArrayName_))
      {
        return false;
      }
    }

    for (auto it = scenePool->objects_.begin(); it != scenePool->objects_.end(); ++it)
    {
      ObjectArchetype* objectArchetype = objectManager.GetObjectArchetype(*it);
      undoComponentArrays_.push_back(objectArchetype->components_[componentArrayName_]);
      objectArchetype->components_.erase(componentArrayName_);
    }

    poolArchetype->RemoveComponentArray(componentArrayName_, &undoIndex_);*/

    return true;
  }

  void DeleteComponentArray::Undo()
  {
    /*Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    ObjectManager& objectManager = space->GetObjectManager();
    PoolArchetype* poolArchetype = objectManager.GetPoolArchetype(poolName_);
    PoolInfo* scenePool = scene->GetPoolInfo(poolName_);

    for (auto it = scenePool->objects_.begin(); it != scenePool->objects_.end(); ++it)
    {
      ObjectArchetype* objectArchetype = objectManager.GetObjectArchetype(*it);
      objectArchetype->components_[componentArrayName_] = undoComponentArrays_.front();
      undoComponentArrays_.erase(undoComponentArrays_.begin());
    }

    poolArchetype->componentArrayNames_.insert(poolArchetype->componentArrayNames_.begin() + undoIndex_, componentArrayName_);*/
  }

  void DeleteComponentArray::Redo()
  {
    /*Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    ObjectManager& objectManager = space->GetObjectManager();
    PoolArchetype* poolArchetype = objectManager.GetPoolArchetype(poolName_);
    PoolInfo* scenePool = scene->GetPoolInfo(poolName_);

    for (auto it = scenePool->objects_.begin(); it != scenePool->objects_.end(); ++it)
    {
      ObjectArchetype* objectArchetype = objectManager.GetObjectArchetype(*it);
      undoComponentArrays_.push_back(objectArchetype->components_[componentArrayName_]);
      objectArchetype->components_.erase(componentArrayName_);
    }

    poolArchetype->RemoveComponentArray(componentArrayName_, &undoIndex_);*/
  }
}