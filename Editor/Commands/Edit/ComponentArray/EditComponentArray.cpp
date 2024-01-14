/* ======================================================================== */
/*!
 * \file            EditComponentArray.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Edits the value of a component array in an object archetype.
 */
 /* ======================================================================== */

#include "EditComponentArray.hpp"
#include <Editor.hpp>

namespace Barrage
{
  EditComponentArray::EditComponentArray(
    const std::string& sceneName,
    const std::string& poolName,
    const std::string& objectName,
    const std::string& componentArrayName,
    bool isSpawnArchetype,
    const rttr::variant& newValue,
    bool chainUndo) :
    Command("Value changed. (" + componentArrayName + ")", chainUndo),
    sceneName_(sceneName),
    poolName_(poolName),
    objectName_(objectName),
    componentArrayName_(componentArrayName),
    isSpawnArchetype_(isSpawnArchetype),
    newValue_(newValue),
    oldValue_()
  {
  }

  bool EditComponentArray::Execute()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);

    if (scene == nullptr || scene->poolArchetypes_.count(poolName_) == 0)
    {
      return false;
    }

    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    if (isSpawnArchetype_ && poolArchetype.spawnArchetypes_.count(objectName_) == 0)
    {
      return false;
    }
    else if (!isSpawnArchetype_ && poolArchetype.startingObjects_.count(objectName_) == 0)
    {
      return false;
    }

    ObjectArchetype& objectArchetype = isSpawnArchetype_ ? 
      poolArchetype.spawnArchetypes_.at(objectName_) : 
      poolArchetype.startingObjects_.at(objectName_);
    
    if (objectArchetype.componentArrays_.count(componentArrayName_) == 0)
    {
      return false;
    }

    ComponentArrayDeepPtr& componentArray = objectArchetype.componentArrays_.at(componentArrayName_);

    if (componentArray->GetCapacity() == 0)
    {
      return false;
    }

    oldValue_ = componentArray->GetRTTRValue(0);
    componentArray->SetRTTRValue(newValue_, 0);

    return true;
  }

  void EditComponentArray::Undo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);
    ObjectArchetype& objectArchetype = isSpawnArchetype_ ?
      poolArchetype.spawnArchetypes_.at(objectName_) :
      poolArchetype.startingObjects_.at(objectName_);
    ComponentArrayDeepPtr& componentArray = objectArchetype.componentArrays_.at(componentArrayName_);

    componentArray->SetRTTRValue(oldValue_, 0);
  }

  void EditComponentArray::Redo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);
    ObjectArchetype& objectArchetype = isSpawnArchetype_ ?
      poolArchetype.spawnArchetypes_.at(objectName_) :
      poolArchetype.startingObjects_.at(objectName_);
    ComponentArrayDeepPtr& componentArray = objectArchetype.componentArrays_.at(componentArrayName_);

    componentArray->SetRTTRValue(newValue_, 0);
  }
}