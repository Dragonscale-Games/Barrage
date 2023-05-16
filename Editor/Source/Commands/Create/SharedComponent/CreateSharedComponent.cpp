/* ======================================================================== */
/*!
 * \file            CreateSharedComponent.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Adds a shared component to a pool archetype.
 */
 /* ======================================================================== */

#include "CreateSharedComponent.hpp"
#include <Editor/Editor.hpp>

namespace Barrage
{
  CreateSharedComponent::CreateSharedComponent(
    const std::string& sceneName,
    const std::string& poolName,
    const std::string_view& sharedComponentName) :
    Command("Added " + std::string(sharedComponentName) + " to " + poolName + "."),
    sceneName_(sceneName),
    poolName_(poolName),
    sharedComponentName_(sharedComponentName),
    redoComponent_(nullptr)
  {
  }

  CreateSharedComponent::~CreateSharedComponent()
  {
    delete redoComponent_;
  }

  bool CreateSharedComponent::Execute()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    if (scene == nullptr)
    {
      return false;
    }

    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    if (poolArchetype == nullptr || poolArchetype->HasSharedComponent(sharedComponentName_))
    {
      return false;
    }

    SharedComponent* sharedComponent = ComponentAllocator::AllocateSharedComponent(sharedComponentName_);

    if (sharedComponent == nullptr)
    {
      return false;
    }

    poolArchetype->AddSharedComponent(sharedComponentName_, sharedComponent);

    return true;
  }

  void CreateSharedComponent::Undo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    redoComponent_ = poolArchetype->ExtractSharedComponent(sharedComponentName_);
  }

  void CreateSharedComponent::Redo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    poolArchetype->AddSharedComponent(sharedComponentName_, redoComponent_);
    redoComponent_ = nullptr;
  }
}