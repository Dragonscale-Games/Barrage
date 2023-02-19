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
    const std::string& spaceName,
    const std::string& poolName,
    const std::string_view& componentName) :
    Command("Added " + std::string(componentName) + " to " + poolName + "."),
    spaceName_(spaceName),
    poolName_(poolName),
    componentName_(componentName),
    redoComponent_(nullptr)
  {
  }

  CreateSharedComponent::~CreateSharedComponent()
  {
    delete redoComponent_;
  }

  bool CreateSharedComponent::Execute()
  {
    Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);

    if (space == nullptr)
    {
      return false;
    }

    ObjectManager& objectManager = space->GetObjectManager();
    ComponentAllocator& componentAllocator = objectManager.GetComponentAllocator();
    PoolArchetype* poolArchetype = objectManager.GetPoolArchetype(poolName_);

    if (poolArchetype == nullptr || poolArchetype->sharedComponents_.count(componentName_))
    {
      return false;
    }

    SharedComponent* component = componentAllocator.AllocateSharedComponent(componentName_);

    if (component == nullptr)
    {
      return false;
    }

    poolArchetype->sharedComponents_[componentName_] = component;

    return true;
  }

  void CreateSharedComponent::Undo()
  {
    Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    ObjectManager& objectManager = space->GetObjectManager();
    PoolArchetype* poolArchetype = objectManager.GetPoolArchetype(poolName_);

    redoComponent_ = poolArchetype->sharedComponents_[componentName_];
    poolArchetype->sharedComponents_.erase(componentName_);
  }

  void CreateSharedComponent::Redo()
  {
    Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    ObjectManager& objectManager = space->GetObjectManager();
    PoolArchetype* poolArchetype = objectManager.GetPoolArchetype(poolName_);

    poolArchetype->sharedComponents_[componentName_] = redoComponent_;
    redoComponent_ = nullptr;
  }
}