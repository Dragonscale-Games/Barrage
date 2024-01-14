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
    const std::string& componentArrayName) :
    Command("Removed " + componentArrayName + " from " + poolName + "."),
    sceneName_(sceneName),
    poolName_(poolName),
    componentArrayName_(componentArrayName),
    undoStartingObjectArrays_(),
    undoSpawnArchetypeArrays_()
  {
  }

  bool DeleteComponentArray::Execute()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);

    if (scene == nullptr || scene->poolArchetypes_.count(poolName_) == 0)
    {
      return false;
    }

    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    if (poolArchetype.componentArrayNames_.count(componentArrayName_) == 0)
    {
      return false;
    }

    RemoveComponentArraysFromObjects(poolArchetype.startingObjects_, undoStartingObjectArrays_);
    RemoveComponentArraysFromObjects(poolArchetype.spawnArchetypes_, undoSpawnArchetypeArrays_);

    poolArchetype.componentArrayNames_.erase(componentArrayName_);

    return true;
  }

  void DeleteComponentArray::Undo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    ReplaceComponentArraysOnObjects(poolArchetype.startingObjects_, undoStartingObjectArrays_);
    ReplaceComponentArraysOnObjects(poolArchetype.spawnArchetypes_, undoSpawnArchetypeArrays_);

    poolArchetype.componentArrayNames_.insert(componentArrayName_);
  }

  void DeleteComponentArray::Redo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    RemoveComponentArraysFromObjects(poolArchetype.startingObjects_, undoStartingObjectArrays_);
    RemoveComponentArraysFromObjects(poolArchetype.spawnArchetypes_, undoSpawnArchetypeArrays_);

    poolArchetype.componentArrayNames_.erase(componentArrayName_);
  }

  void DeleteComponentArray::RemoveComponentArraysFromObjects(ObjectArchetypeMap& objects, ComponentArrayMap& arrayMap)
  {
    for (auto it = objects.begin(); it != objects.end(); ++it)
    {
      std::string objectName = it->first;
      ObjectArchetype& objectArchetype = it->second;
      
      arrayMap.emplace(objectName, objectArchetype.componentArrays_.at(componentArrayName_));
      objectArchetype.componentArrays_.erase(componentArrayName_);
    }
  }

  void DeleteComponentArray::ReplaceComponentArraysOnObjects(ObjectArchetypeMap& objects, ComponentArrayMap& arrayMap)
  {
    for (auto it = objects.begin(); it != objects.end(); ++it)
    {
      std::string objectName = it->first;
      ObjectArchetype& objectArchetype = it->second;

      objectArchetype.componentArrays_.emplace(componentArrayName_, arrayMap.at(objectName));
      arrayMap.erase(objectName);
    }
  }
}