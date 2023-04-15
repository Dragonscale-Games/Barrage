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
    const std::string& spaceName,
    const std::string& poolName,
    const std::string_view& componentName) :
    Command("Removed " + std::string(componentName) + " from " + poolName + "."),
    spaceName_(spaceName),
    poolName_(poolName),
    componentName_(componentName),
    undoComponent_(nullptr)
  {
  }

  DeleteSharedComponent::~DeleteSharedComponent()
  {
    delete undoComponent_;
  }

  bool DeleteSharedComponent::Execute()
  {
    /*Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);

    if (space == nullptr)
    {
      return false;
    }

    ObjectManager& objectManager = space->GetObjectManager();
    PoolArchetype* poolArchetype = objectManager.GetPoolArchetype(poolName_);

    if (poolArchetype == nullptr || !poolArchetype->sharedComponents_.count(componentName_))
    {
      return false;
    }

    undoComponent_ = poolArchetype->sharedComponents_.at(componentName_);
    poolArchetype->sharedComponents_.erase(componentName_);*/

    return true;
  }

  void DeleteSharedComponent::Undo()
  {
    /*Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    ObjectManager& objectManager = space->GetObjectManager();
    PoolArchetype* poolArchetype = objectManager.GetPoolArchetype(poolName_);

    poolArchetype->sharedComponents_[componentName_] = undoComponent_;
    undoComponent_ = nullptr;*/
  }

  void DeleteSharedComponent::Redo()
  {
    /*Space* space = Engine::Instance->Spaces().GetSpace(spaceName_);
    ObjectManager& objectManager = space->GetObjectManager();
    PoolArchetype* poolArchetype = objectManager.GetPoolArchetype(poolName_);

    undoComponent_ = poolArchetype->sharedComponents_.at(componentName_);
    poolArchetype->sharedComponents_.erase(componentName_);*/
  }
}
