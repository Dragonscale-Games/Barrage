/* ======================================================================== */
/*!
 * \file            CreatePool.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Creates a new (empty) pool archetype and adds that archetype to the scene.
 */
 /* ======================================================================== */

#include "CreatePool.hpp"
#include "Editor/Editor.hpp"

namespace Barrage
{
  std::stack<PoolArchetype*> CreatePool::redoArchetypes_ = std::stack<PoolArchetype*>();
  
  CreatePool::CreatePool(const std::string& spaceName, const std::string& sceneName) :
    Command("New pool created."),
    spaceName_(spaceName),
    sceneName_(sceneName),
    poolName_()
  {
  }
 
  bool CreatePool::Execute()
  {
    Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    
    if (space == nullptr)
    {
      return false;
    }

    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    if (scene == nullptr)
    {
      return false;
    }

    ObjectManager& objectManager = space->GetObjectManager();

    unsigned counter = 0;

    do {
      poolName_ = "New Pool";

      if (counter)
      {
        poolName_ += " ";
        poolName_ += std::to_string(counter);
      }

      counter++;

    } while (objectManager.GetPoolArchetype(poolName_));

    if (scene->HasPool(poolName_))
    {
      return false;
    }

    objectManager.CreatePoolArchetype(poolName_);

    if (objectManager.GetPoolArchetype(poolName_) == nullptr)
    {
      return false;
    }

    scene->AddStartingPool(poolName_);

    return true;
  }

  void CreatePool::Undo()
  {
    Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    ObjectManager& objectManager = space->GetObjectManager();

    PoolArchetype* removedArchetype = objectManager.ExtractPoolArchetype(poolName_);
    redoArchetypes_.push(removedArchetype);
    scene->startingPools_.erase(poolName_);
  }

  void CreatePool::Redo()
  {
    Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    ObjectManager& objectManager = space->GetObjectManager();

    objectManager.AddPoolArchetype(poolName_, redoArchetypes_.top());
    redoArchetypes_.pop();
    scene->AddStartingPool(poolName_);
  }

  void CreatePool::ClearRedos()
  {
    while (!redoArchetypes_.empty())
    {
      delete redoArchetypes_.top();
      redoArchetypes_.pop();
    }
  }
}