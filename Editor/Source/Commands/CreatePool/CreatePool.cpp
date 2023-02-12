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

    if (poolName_.empty())
    {
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

    // this should never happen
    if (space == nullptr)
    {
      return;
    }

    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    // this should never happen
    if (scene == nullptr)
    {
      return;
    }
    
    space->GetObjectManager().DeletePoolArchetype(poolName_);

    for (auto it = scene->startingPools_.begin(); it != scene->startingPools_.end(); ++it)
    {
      if (it->poolName_ == poolName_)
      {
        scene->startingPools_.erase(it);
        return;
      }
    }
  }
}