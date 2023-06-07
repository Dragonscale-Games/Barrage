/* ======================================================================== */
/*!
 * \file            CreateComponent.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Adds a component to a pool archetype.
 */
 /* ======================================================================== */

#include "CreateComponent.hpp"
#include <Editor.hpp>

namespace Barrage
{
  CreateComponent::CreateComponent(
    const std::string& sceneName,
    const std::string& poolName,
    const std::string_view& componentName) :
    Command("Added " + std::string(componentName) + " to " + poolName + "."),
    sceneName_(sceneName),
    poolName_(poolName),
    componentName_(componentName),
    redoComponent_(nullptr)
  {
  }

  CreateComponent::~CreateComponent()
  {
    delete redoComponent_;
  }

  bool CreateComponent::Execute()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    if (scene == nullptr)
    {
      return false;
    }

    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    if (poolArchetype == nullptr || poolArchetype->HasComponent(componentName_))
    {
      return false;
    }

    Component* component = ComponentAllocator::AllocateComponent(componentName_);

    if (component == nullptr)
    {
      return false;
    }

    poolArchetype->AddComponent(componentName_, component);

    return true;
  }

  void CreateComponent::Undo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    redoComponent_ = poolArchetype->ExtractComponent(componentName_);
  }

  void CreateComponent::Redo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    poolArchetype->AddComponent(componentName_, redoComponent_);
    redoComponent_ = nullptr;
  }
}