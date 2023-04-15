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
    const std::string& spaceName,
    const std::string& sceneName,
    const std::string& poolName,
    const std::string_view& componentArrayName) :
    Command("Added " + std::string(componentArrayName) + " to " + poolName + "."),
    spaceName_(spaceName),
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
      delete *it;
    }
  }

  bool CreateComponentArray::Execute()
  {
    /*Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    if (space == nullptr || scene == nullptr || !scene->HasPool(poolName_))
    {
      return false;
    }

    ObjectManager& objectManager = space->GetObjectManager();
    ComponentAllocator& componentAllocator = objectManager.GetComponentAllocator();
    PoolArchetype* poolArchetype = objectManager.GetPoolArchetype(poolName_);
    PoolInfo* scenePool = scene->GetPoolInfo(poolName_);

    if (poolArchetype == nullptr || scenePool == nullptr || poolArchetype->HasComponentArray(componentArrayName_))
    {
      return false;
    }

    for (auto it = scenePool->objects_.begin(); it != scenePool->objects_.end(); ++it)
    {
      if (objectManager.GetObjectArchetype(*it) == nullptr)
      {
        return false;
      }
    }

    for (auto it = scenePool->objects_.begin(); it != scenePool->objects_.end(); ++it)
    {
      ObjectArchetype* objectArchetype = objectManager.GetObjectArchetype(*it);
      ComponentArray* componentArray = componentAllocator.AllocateComponentArray(componentArrayName_, 1);

      if (componentArray == nullptr || objectArchetype->components_.count(componentArrayName_))
      {
        return false;
      }

      objectArchetype->components_[componentArrayName_] = componentArray;
    }

    poolArchetype->componentArrayNames_.push_back(componentArrayName_);*/

    return true;
  }

  void CreateComponentArray::Undo()
  {
    /*Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    ObjectManager& objectManager = space->GetObjectManager();
    PoolArchetype* poolArchetype = objectManager.GetPoolArchetype(poolName_);
    PoolInfo* scenePool = scene->GetPoolInfo(poolName_);

    for (auto it = scenePool->objects_.begin(); it != scenePool->objects_.end(); ++it)
    {
      ObjectArchetype* objectArchetype = objectManager.GetObjectArchetype(*it);
      redoComponentArrays_.push_back(objectArchetype->components_[componentArrayName_]);
      objectArchetype->components_.erase(componentArrayName_);
    }

    poolArchetype->componentArrayNames_.pop_back();*/
  }

  void CreateComponentArray::Redo()
  {
    /*Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    ObjectManager& objectManager = space->GetObjectManager();
    PoolArchetype* poolArchetype = objectManager.GetPoolArchetype(poolName_);
    PoolInfo* scenePool = scene->GetPoolInfo(poolName_);

    for (auto it = scenePool->objects_.begin(); it != scenePool->objects_.end(); ++it)
    {
      ObjectArchetype* objectArchetype = objectManager.GetObjectArchetype(*it);
      objectArchetype->components_[componentArrayName_] = redoComponentArrays_.front();
      redoComponentArrays_.erase(redoComponentArrays_.begin());
    }

    poolArchetype->componentArrayNames_.push_back(componentArrayName_);*/
  }
}