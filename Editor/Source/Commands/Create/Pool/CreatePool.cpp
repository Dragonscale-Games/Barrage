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
  CreatePool::CreatePool(const std::string& sceneName) :
    Command("New pool created."),
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
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    if (scene == nullptr)
    {
      return false;
    }

    unsigned counter = 0;

    do {
      poolName_ = "Pool";

      if (counter)
      {
        poolName_ += " ";
        poolName_ += std::to_string(counter);
      }

      counter++;

    } while (scene->GetPoolArchetype(poolName_));

    scene->AddPoolArchetype(new PoolArchetype(poolName_, 1));

    return true;
  }

  void CreatePool::Undo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    redoArchetype_ = scene->ExtractPoolArchetype(poolName_);

    if (Editor::Instance->Data().selectedPool_ == poolName_)
    {
      Editor::Instance->Data().selectedPool_ = std::string();
    }
  }

  void CreatePool::Redo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    scene->AddPoolArchetype(redoArchetype_);
    redoArchetype_ = nullptr;
  }
}