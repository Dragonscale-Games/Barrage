/* ======================================================================== */
/*!
 * \file            DuplicatePool.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Duplicates an existing pool archetype in the scene.
 */
 /* ======================================================================== */

#include "DuplicatePool.hpp"
#include "Editor.hpp"

namespace Barrage
{
  DuplicatePool::DuplicatePool(const std::string& sceneName, const std::string& poolName) :
    Command("New pool created."),
    sceneName_(sceneName),
    poolName_(poolName),
    redoArchetype_(nullptr)
  {
  }

  DuplicatePool::~DuplicatePool()
  {
    delete redoArchetype_;
  }

  bool DuplicatePool::Execute()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    if (scene == nullptr)
    {
      return false;
    }

    PoolArchetype* originalPool = scene->GetPoolArchetype(poolName_);

    if (originalPool == nullptr)
    {
      return false;
    }

    PoolArchetype* newPool = new PoolArchetype(*originalPool);

    unsigned counter = 2;

    do {
      poolName_ = originalPool->GetName() + " " + std::to_string(counter);
      counter++;

    } while (scene->GetPoolArchetype(poolName_));

    newPool->SetName(poolName_);

    scene->AddPoolArchetype(newPool);

    return true;
  }

  void DuplicatePool::Undo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    redoArchetype_ = scene->ExtractPoolArchetype(poolName_);

    if (Editor::Instance->Data().selectedPool_ == poolName_)
    {
      Editor::Instance->Data().selectedPool_ = std::string();
    }
  }

  void DuplicatePool::Redo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    scene->AddPoolArchetype(redoArchetype_);
    redoArchetype_ = nullptr;
  }
}