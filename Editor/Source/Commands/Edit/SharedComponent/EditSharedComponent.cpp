/* ======================================================================== */
/*!
 * \file            EditSharedComponent.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Edits the value of a shared component in an pool archetype.
 */
 /* ======================================================================== */

#include "EditSharedComponent.hpp"
#include <Editor/Editor.hpp>

namespace Barrage
{
  EditSharedComponent::EditSharedComponent(
    const std::string& sceneName,
    const std::string& poolName,
    const std::string_view& sharedComponentName,
    const rttr::variant& newValue,
    bool chainUndo) :
    Command("Value changed. (" + std::string(sharedComponentName.data()) + ")", chainUndo),
    sceneName_(sceneName),
    poolName_(poolName),
    sharedComponentName_(sharedComponentName),
    newValue_(newValue),
    oldValue_()
  {
  }

  bool EditSharedComponent::Execute()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    if (scene == nullptr)
    {
      return false;
    }

    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    if (poolArchetype == nullptr)
    {
      return false;
    }

    SharedComponent* sharedComponent = poolArchetype->GetSharedComponent(sharedComponentName_);

    if (sharedComponent == nullptr)
    {
      return false;
    }

    oldValue_ = sharedComponent->GetRTTRValue();
    sharedComponent->SetRTTRValue(newValue_);

    return true;
  }

  void EditSharedComponent::Undo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);
    SharedComponent* sharedComponent = poolArchetype->GetSharedComponent(sharedComponentName_);

    sharedComponent->SetRTTRValue(oldValue_);
  }

  void EditSharedComponent::Redo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);
    SharedComponent* sharedComponent = poolArchetype->GetSharedComponent(sharedComponentName_);

    sharedComponent->SetRTTRValue(newValue_);
  }
}