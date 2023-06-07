/* ======================================================================== */
/*!
 * \file            EditComponent.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Edits the value of a component in an pool archetype.
 */
 /* ======================================================================== */

#include "EditComponent.hpp"
#include <Editor.hpp>

namespace Barrage
{
  EditComponent::EditComponent(
    const std::string& sceneName,
    const std::string& poolName,
    const std::string_view& componentName,
    const rttr::variant& newValue,
    bool chainUndo) :
    Command("Value changed. (" + std::string(componentName.data()) + ")", chainUndo),
    sceneName_(sceneName),
    poolName_(poolName),
    componentName_(componentName),
    newValue_(newValue),
    oldValue_()
  {
  }

  bool EditComponent::Execute()
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

    Component* component = poolArchetype->GetComponent(componentName_);

    if (component == nullptr)
    {
      return false;
    }

    oldValue_ = component->GetRTTRValue();
    component->SetRTTRValue(newValue_);

    return true;
  }

  void EditComponent::Undo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);
    Component* component = poolArchetype->GetComponent(componentName_);

    component->SetRTTRValue(oldValue_);
  }

  void EditComponent::Redo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);
    Component* component = poolArchetype->GetComponent(componentName_);

    component->SetRTTRValue(newValue_);
  }
}