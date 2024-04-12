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
#include "Editor.hpp"

namespace Barrage
{
  DeleteComponent::DeleteComponent(
    const std::string& sceneName,
    const std::string& poolName,
    const std::string& componentName) :
    Command("Removed " + componentName + " from " + poolName + "."),
    sceneName_(sceneName),
    poolName_(poolName),
    componentName_(componentName),
    undoComponent_(nullptr)
  {
  }

  bool DeleteComponent::Execute()
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

    undoComponent_ = poolArchetype.components_.at(componentName_);
    poolArchetype.components_.erase(componentName_);

    return true;
  }

  void DeleteComponent::Undo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);
    
    poolArchetype.components_.emplace(componentName_, undoComponent_);
    undoComponent_ = nullptr;
  }

  void DeleteComponent::Redo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);
    
    undoComponent_ = poolArchetype.components_.at(componentName_);
    poolArchetype.components_.erase(componentName_);
  }
}
