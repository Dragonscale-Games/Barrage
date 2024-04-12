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
#include "Editor.hpp"
#include "Objects/Components/ComponentFactory.hpp"

namespace Barrage
{
  CreateComponentArray::CreateComponentArray(
    const std::string& sceneName,
    const std::string& poolName,
    const std::string& componentArrayName) :
    Command("Added " + std::string(componentArrayName) + " to " + poolName + "."),
    sceneName_(sceneName),
    poolName_(poolName),
    componentArrayName_(componentArrayName)
  {
  }

  bool CreateComponentArray::Execute()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);

    if (scene == nullptr || scene->poolArchetypes_.count(poolName_) == 0)
    {
      return false;
    }

    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    if (poolArchetype.componentArrayNames_.count(componentArrayName_))
    {
      return false;
    }
    
    if (AddComponentArraysToObjects(poolArchetype.startingObjects_) == false)
    {
      return false;
    }

    if (AddComponentArraysToObjects(poolArchetype.spawnArchetypes_) == false)
    {
      return false;
    }

    poolArchetype.componentArrayNames_.insert(componentArrayName_);

    return true;
  }

  void CreateComponentArray::Undo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    RemoveComponentArraysFromObjects(poolArchetype.startingObjects_);
    RemoveComponentArraysFromObjects(poolArchetype.spawnArchetypes_);

    poolArchetype.componentArrayNames_.erase(componentArrayName_);
  }

  void CreateComponentArray::Redo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    AddComponentArraysToObjects(poolArchetype.startingObjects_);
    AddComponentArraysToObjects(poolArchetype.spawnArchetypes_);

    poolArchetype.componentArrayNames_.insert(componentArrayName_);
  }

  bool CreateComponentArray::AddComponentArraysToObjects(ObjectArchetypeMap& objects)
  {
    for (auto it = objects.begin(); it != objects.end(); ++it)
    {
      ObjectArchetype& objectArchetype = it->second;
      DeepPtr<ComponentArray> componentArray = ComponentFactory::AllocateComponentArray(componentArrayName_, 1);

      if (!componentArray)
      {
        return false;
      }

      if (objectArchetype.componentArrays_.count(componentArrayName_))
      {
        throw std::runtime_error("Object had component array that pool didn't.");
      }

      objectArchetype.componentArrays_.emplace(componentArrayName_, componentArray);
    }

    return true;
  }

  void CreateComponentArray::RemoveComponentArraysFromObjects(ObjectArchetypeMap& objects)
  {
    for (auto it = objects.begin(); it != objects.end(); ++it)
    {
      it->second.componentArrays_.erase(componentArrayName_);
    }
  }
}