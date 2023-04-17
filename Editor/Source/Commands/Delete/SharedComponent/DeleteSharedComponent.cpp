/* ======================================================================== */
/*!
 * \file            DeleteSharedComponent.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Removes a shared component from a pool archetype.
 */
 /* ======================================================================== */

#include "DeleteSharedComponent.hpp"
#include <Editor/Editor.hpp>

namespace Barrage
{
  DeleteSharedComponent::DeleteSharedComponent(
    const std::string& sceneName,
    const std::string& poolName,
    const std::string_view& sharedComponentName) :
    Command("Removed " + std::string(sharedComponentName) + " from " + poolName + "."),
    sceneName_(sceneName),
    poolName_(poolName),
    sharedComponentName_(sharedComponentName),
    undoComponent_(nullptr)
  {
  }

  DeleteSharedComponent::~DeleteSharedComponent()
  {
    delete undoComponent_;
  }

  bool DeleteSharedComponent::Execute()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    if (scene == nullptr)
    {
      return false;
    }

    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    if (poolArchetype == nullptr || !poolArchetype->HasSharedComponent(sharedComponentName_))
    {
      return false;
    }

    undoComponent_ = poolArchetype->ExtractSharedComponent(sharedComponentName_);

    return true;
  }

  void DeleteSharedComponent::Undo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);
    
    poolArchetype->AddSharedComponent(sharedComponentName_, undoComponent_);
    undoComponent_ = nullptr;
  }

  void DeleteSharedComponent::Redo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);
    
    undoComponent_ = poolArchetype->ExtractSharedComponent(sharedComponentName_);
  }
}
