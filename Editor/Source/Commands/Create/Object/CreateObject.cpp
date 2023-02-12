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
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    if (space == nullptr || scene == nullptr || !scene->HasPool(poolName_))
    {
      return false;
    }

    ObjectManager& objectManager = space->GetObjectManager();
    PoolArchetype* poolArchetype = objectManager.GetPoolArchetype(poolName_);
    PoolInfo* scenePool = scene->GetPoolInfo(poolName_);

    if (poolArchetype == nullptr || scenePool == nullptr)
    {
      return false;
    }

    if (scenePool->objects_.size() >= poolArchetype->capacity_)
    {
      LogWidget::AddEntry("Error: Could not create object (pool is full).");
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

    if (scene->HasObject(poolName_, objectName_))
    {
      return false;
    }

    objectManager.CreateObjectArchetype(objectName_, poolArchetype->componentArrayNames_);

    if (objectManager.GetObjectArchetype(objectName_) == nullptr)
    {
      return false;
    }

    scenePool->objects_.push_back(objectName_);

    return true;
  }

  void CreateObject::Undo()
  {
    Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    ObjectManager& objectManager = space->GetObjectManager();

    ObjectArchetype* removedArchetype = objectManager.ExtractObjectArchetype(objectName_);
    redoArchetypes_.push(removedArchetype);
    scene->RemoveObject(poolName_, objectName_);

    if (Editor::Instance->Data().selectedObject_ == objectName_)
    {
      Editor::Instance->Data().selectedObject_ = std::string();
    }
  }

  void CreateObject::Redo()
  {
    Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    ObjectManager& objectManager = space->GetObjectManager();

    objectManager.AddObjectArchetype(objectName_, redoArchetypes_.top());
    redoArchetypes_.pop();
    scene->AddObject(poolName_, objectName_);
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