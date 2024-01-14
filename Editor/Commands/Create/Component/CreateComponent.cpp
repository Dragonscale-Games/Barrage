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
#include "Editor.hpp"
#include "Objects/Components/ComponentFactory.hpp"

namespace Barrage
{
  CreateComponent::CreateComponent(
    const std::string& sceneName,
    const std::string& poolName,
    const std::string& componentName) :
    Command("Added " + std::string(componentName) + " to " + poolName + "."),
    sceneName_(sceneName),
    poolName_(poolName),
    componentName_(componentName)
  {
  }

  bool CreateComponent::Execute()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);

    if (scene == nullptr || scene->poolArchetypes_.count(poolName_) == 0)
    {
      return false;
    }

    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    if (poolArchetype.components_.count(componentName_))
    {
      return false;
    }

    ComponentDeepPtr component = ComponentFactory::AllocateComponent(componentName_);

    if (!component)
    {
      return false;
    }

    poolArchetype.components_.emplace(componentName_, component);

    return true;
  }

  void CreateComponent::Undo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    poolArchetype.components_.erase(componentName_);
  }

  void CreateComponent::Redo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    ComponentDeepPtr component = ComponentFactory::AllocateComponent(componentName_);
    poolArchetype.components_.emplace(componentName_, component);
  }
}