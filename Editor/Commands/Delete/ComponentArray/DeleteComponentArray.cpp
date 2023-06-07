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
#include <Editor.hpp>

namespace Barrage
{
  DeleteComponentArray::DeleteComponentArray(
    const std::string& sceneName,
    const std::string& poolName,
    const std::string_view& componentArrayName) :
    Command("Removed " + std::string(componentArrayName) + " from " + poolName + "."),
    sceneName_(sceneName),
    poolName_(poolName),
    componentArrayName_(componentArrayName),
    undoIndex_(),
    undoComponentArrays_()
  {
  }

  DeleteComponentArray::~DeleteComponentArray()
  {
    for (auto it = undoComponentArrays_.begin(); it != undoComponentArrays_.end(); ++it)
    {
      delete it->second;
    }
  }

  bool DeleteComponentArray::Execute()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    if (scene == nullptr)
    {
      return false;
    }

    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    if (poolArchetype == nullptr || !poolArchetype->HasComponentArray(componentArrayName_))
    {
      return false;
    }

    const std::vector<ObjectArchetype*> startingObjects = poolArchetype->GetStartingObjects();
    const std::vector<ObjectArchetype*> spawnArchetypes = poolArchetype->GetSpawnArchetypes();

    RemoveComponentArraysFromObjects(startingObjects);
    RemoveComponentArraysFromObjects(spawnArchetypes);

    poolArchetype->RemoveComponentArrayName(componentArrayName_, &undoIndex_);

    return true;
  }

  void DeleteComponentArray::Undo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    const std::vector<ObjectArchetype*> startingObjects = poolArchetype->GetStartingObjects();
    const std::vector<ObjectArchetype*> spawnArchetypes = poolArchetype->GetSpawnArchetypes();

    ReplaceComponentArraysOnObjects(startingObjects);
    ReplaceComponentArraysOnObjects(spawnArchetypes);

    poolArchetype->AddComponentArrayName(componentArrayName_, &undoIndex_);
  }

  void DeleteComponentArray::Redo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    const std::vector<ObjectArchetype*> startingObjects = poolArchetype->GetStartingObjects();
    const std::vector<ObjectArchetype*> spawnArchetypes = poolArchetype->GetSpawnArchetypes();
    
    RemoveComponentArraysFromObjects(startingObjects);
    RemoveComponentArraysFromObjects(spawnArchetypes);
    
    poolArchetype->RemoveComponentArrayName(componentArrayName_, &undoIndex_);
  }

  void DeleteComponentArray::ReplaceComponentArraysOnObjects(const std::vector<ObjectArchetype*>& objects)
  {
    for (auto it = objects.begin(); it != objects.end(); ++it)
    {
      ObjectArchetype* objectArchetype = *it;
      std::string objectName = objectArchetype->GetName();
      ComponentArray* componentArray = undoComponentArrays_.at(objectName);

      // remove from temp storage
      undoComponentArrays_.erase(objectName);
      // add to object
      objectArchetype->AddComponentArray(componentArrayName_, componentArray);
    }
  }

  void DeleteComponentArray::RemoveComponentArraysFromObjects(const std::vector<ObjectArchetype*>& objects)
  {
    for (auto it = objects.begin(); it != objects.end(); ++it)
    {
      ObjectArchetype* objectArchetype = *it;
      std::string objectName = objectArchetype->GetName();

      // remove from object
      ComponentArray* componentArray = objectArchetype->ExtractComponentArray(componentArrayName_);
      // add to temp storage
      undoComponentArrays_.insert(std::make_pair(objectName, componentArray));
    }
  }
}