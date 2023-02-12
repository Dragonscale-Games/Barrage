/* ======================================================================== */
/*!
 * \file            CreateObject.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Creates a new (empty) object archetype and adds that object to a pool
   in the scene.
 */
 /* ======================================================================== */

#include "CreateObject.hpp"
#include "Editor/Editor.hpp"

namespace Barrage
{
  std::stack<ObjectArchetype*> CreateObject::redoArchetypes_ = std::stack<ObjectArchetype*>();
  
  CreateObject::CreateObject(const std::string& spaceName, const std::string& sceneName, const std::string& poolName) :
    Command("New object created in " + poolName + "."),
    spaceName_(spaceName),
    sceneName_(sceneName),
    poolName_(poolName),
    objectName_()
  {
  }

  bool CreateObject::Execute()
  {
    Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);

    if (space == nullptr)
    {
      return false;
    }

    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    if (scene == nullptr || !scene->HasPool(poolName_))
    {
      return false;
    }

    ObjectManager& objectManager = space->GetObjectManager();

    PoolArchetype* poolArchetype = objectManager.GetPoolArchetype(poolName_);

    if (poolArchetype == nullptr)
    {
      return false;
    }

    PoolInfo& scenePool = scene->startingPools_.at(poolName_);

    if (scenePool.objects_.size() >= poolArchetype->capacity_)
    {
      Editor::Instance->Log().AddEntry("Error: Could not create object (pool is full).");
      return false;
    }

    if (objectName_.empty())
    {
      unsigned counter = 0;

      do {
        objectName_ = "New Object";

        if (counter)
        {
          objectName_ += " ";
          objectName_ += std::to_string(counter);
        }

        counter++;

      } while (objectManager.GetObjectArchetype(objectName_));
    }
    
    objectManager.CreateObjectArchetype(objectName_, poolArchetype->componentArrayNames_);

    if (objectManager.GetObjectArchetype(objectName_) == nullptr)
    {
      return false;
    }

    scenePool.objects_.insert(objectName_);

    return true;
  }

  void CreateObject::Undo()
  {
    Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    ObjectManager& objectManager = space->GetObjectManager();
    PoolInfo& scenePool = scene->startingPools_.at(poolName_);

    ObjectArchetype* removedArchetype = objectManager.ExtractObjectArchetype(objectName_);
    redoArchetypes_.push(removedArchetype);
    scenePool.objects_.erase(objectName_);
  }

  void CreateObject::Redo()
  {
    Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    ObjectManager& objectManager = space->GetObjectManager();
    PoolInfo& scenePool = scene->startingPools_.at(poolName_);

    objectManager.AddObjectArchetype(objectName_, redoArchetypes_.top());
    redoArchetypes_.pop();
    scenePool.objects_.insert(objectName_);
  }

  void CreateObject::ClearRedos()
  {
    while (!redoArchetypes_.empty())
    {
      delete redoArchetypes_.top();
      redoArchetypes_.pop();
    }
  }
}