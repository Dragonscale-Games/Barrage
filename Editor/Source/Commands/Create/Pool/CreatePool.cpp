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
  CreatePool::CreatePool(const std::string& spaceName, const std::string& sceneName) :
    Command("New pool created."),
    spaceName_(spaceName),
    sceneName_(sceneName),
    poolName_(),
    redoArchetype_(nullptr)
  {
  }
 
  CreatePool::~CreatePool()
  {
    delete redoArchetype_;
  }

  bool CreatePool::Execute()
  {
    /*Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    if (space == nullptr || scene == nullptr)
    {
      return false;
    }

    ObjectManager& objectManager = space->GetObjectManager();

    unsigned counter = 0;

    do {
      poolName_ = "Pool";

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

    scene->AddStartingPool(poolName_);*/

    return true;
  }

  void CreatePool::Undo()
  {
    /*Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    ObjectManager& objectManager = space->GetObjectManager();

    redoArchetype_ = objectManager.ExtractPoolArchetype(poolName_);
    scene->RemovePool(poolName_);

    if (Editor::Instance->Data().selectedPool_ == poolName_)
    {
      Editor::Instance->Data().selectedPool_ = std::string();
    }*/
  }

  void CreatePool::Redo()
  {
    /*Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    ObjectManager& objectManager = space->GetObjectManager();

    objectManager.AddPoolArchetype(poolName_, redoArchetype_);
    redoArchetype_ = nullptr;
    scene->AddStartingPool(poolName_);*/
  }
}