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
    const std::string& componentName,
    const rttr::variant& newValue,
    bool chainUndo) :
    Command("Value changed. (" + componentName + ")", chainUndo),
    sceneName_(sceneName),
    poolName_(poolName),
    componentName_(componentName),
    newValue_(newValue),
    oldValue_()
  {
  }

  bool EditComponent::Execute()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);

    if (scene == nullptr || scene->poolArchetypes_.count(poolName_) == 0)
    {
      return false;
    }

    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    if (poolArchetype.components_.count(componentName_) == 0)
    {
      return false;
    }

    ComponentDeepPtr& component = poolArchetype.components_.at(componentName_);

    oldValue_ = component->GetRTTRValue();
    component->SetRTTRValue(newValue_);

    return true;
  }

  void EditComponent::Undo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);
    ComponentDeepPtr& component = poolArchetype.components_.at(componentName_);

    component->SetRTTRValue(oldValue_);
  }

  void EditComponent::Redo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);
    ComponentDeepPtr& component = poolArchetype.components_.at(componentName_);

    component->SetRTTRValue(newValue_);
  }
}