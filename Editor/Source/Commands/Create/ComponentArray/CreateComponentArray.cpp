/* ======================================================================== */
/*!
 * \file            CreateComponentArray.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Adds a component array to a pool archetype and adds the corresponding
   component to each of the pool's object archetypes.
 */
 /* ======================================================================== */

#include "CreateComponentArray.hpp"
#include <Editor/Editor.hpp>

namespace Barrage
{
  CreateComponentArray::CreateComponentArray(
    const std::string& sceneName,
    const std::string& poolName,
    const std::string_view& componentArrayName) :
    Command("Added " + std::string(componentArrayName) + " to " + poolName + "."),
    sceneName_(sceneName),
    poolName_(poolName),
    componentArrayName_(componentArrayName),
    redoComponentArrays_()
  {
  }

  CreateComponentArray::~CreateComponentArray()
  {
    for (auto it = redoComponentArrays_.begin(); it != redoComponentArrays_.end(); ++it)
    {
      delete it->second;
    }
  }

  bool CreateComponentArray::Execute()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    if (scene == nullptr)
    {
      return false;
    }

    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    if (poolArchetype == nullptr || poolArchetype->HasComponentArray(componentArrayName_))
    {
      return false;
    }

    const std::vector<ObjectArchetype*>& startingObjects = poolArchetype->GetStartingObjects();
    for (auto it = startingObjects.begin(); it != startingObjects.end(); ++it)
    {
      ObjectArchetype* objectArchetype = *it;
      ComponentArray* componentArray = ComponentAllocator::AllocateComponentArray(componentArrayName_, 1);

      if (componentArray == nullptr || objectArchetype->HasComponentArray(componentArrayName_))
      {
        return false;
      }

      objectArchetype->AddComponentArray(componentArrayName_, componentArray);
    }

    poolArchetype->AddComponentArrayName(componentArrayName_);

    return true;
  }

  void CreateComponentArray::Undo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    const std::vector<ObjectArchetype*>& startingObjects = poolArchetype->GetStartingObjects();
    const std::vector<ObjectArchetype*>& spawnArchetypes = poolArchetype->GetSpawnArchetypes();

    RemoveComponentArraysFromObjects(startingObjects);
    RemoveComponentArraysFromObjects(spawnArchetypes);

    poolArchetype->RemoveComponentArrayName(componentArrayName_);
  }

  void CreateComponentArray::Redo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    const std::vector<ObjectArchetype*>& startingObjects = poolArchetype->GetStartingObjects();
    const std::vector<ObjectArchetype*>& spawnArchetypes = poolArchetype->GetSpawnArchetypes();

    ReplaceComponentArraysOnObjects(startingObjects);
    ReplaceComponentArraysOnObjects(spawnArchetypes);

    poolArchetype->AddComponentArrayName(componentArrayName_);
  }

  void CreateComponentArray::RemoveComponentArraysFromObjects(const std::vector<ObjectArchetype*>& objects)
  {
    for (auto it = objects.begin(); it != objects.end(); ++it)
    {
      ObjectArchetype* objectArchetype = *it;
      std::string objectName = objectArchetype->GetName();

      // remove from object
      ComponentArray* componentArray = objectArchetype->ExtractComponentArray(componentArrayName_);
      // add to temp storage
      redoComponentArrays_.insert(std::make_pair(objectName, componentArray));
    }
  }

  void CreateComponentArray::ReplaceComponentArraysOnObjects(const std::vector<ObjectArchetype*>& objects)
  {
    for (auto it = objects.begin(); it != objects.end(); ++it)
    {
      ObjectArchetype* objectArchetype = *it;
      std::string objectName = objectArchetype->GetName();
      ComponentArray* componentArray = redoComponentArrays_.at(objectName);

      // remove from temp storage
      redoComponentArrays_.erase(objectName);
      // add to object
      objectArchetype->AddComponentArray(componentArrayName_, componentArray);
    }
  }
}