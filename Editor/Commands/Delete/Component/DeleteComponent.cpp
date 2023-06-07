/* ======================================================================== */
/*!
 * \file            DeleteComponent.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Removes a component from a pool archetype.
 */
 /* ======================================================================== */

#include "DeleteComponent.hpp"
#include <Editor.hpp>

namespace Barrage
{
  DeleteComponent::DeleteComponent(
    const std::string& sceneName,
    const std::string& poolName,
    const std::string_view& componentName) :
    Command("Removed " + std::string(componentName) + " from " + poolName + "."),
    sceneName_(sceneName),
    poolName_(poolName),
    componentName_(componentName),
    undoComponent_(nullptr)
  {
  }

  DeleteComponent::~DeleteComponent()
  {
    delete undoComponent_;
  }

  bool DeleteComponent::Execute()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    if (scene == nullptr)
    {
      return false;
    }

    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    if (poolArchetype == nullptr || !poolArchetype->HasComponent(componentName_))
    {
      return false;
    }

    undoComponent_ = poolArchetype->ExtractComponent(componentName_);

    return true;
  }

  void DeleteComponent::Undo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);
    
    poolArchetype->AddComponent(componentName_, undoComponent_);
    undoComponent_ = nullptr;
  }

  void DeleteComponent::Redo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);
    
    undoComponent_ = poolArchetype->ExtractComponent(componentName_);
  }
}
