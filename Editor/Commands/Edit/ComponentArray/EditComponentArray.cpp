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
    const std::string_view& componentArrayName,
    const rttr::variant& newValue,
    bool chainUndo) :
    Command("Value changed. (" + std::string(componentArrayName.data()) + ")", chainUndo),
    sceneName_(sceneName),
    poolName_(poolName),
    componentArrayName_(componentArrayName),
    objectName_(objectName),
    newValue_(newValue),
    oldValue_()
  {
  }

  bool EditComponentArray::Execute()
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

    ObjectArchetype* objectArchetype = poolArchetype->GetObjectArchetype(objectName_);

    if (objectArchetype == nullptr)
    {
      return false;
    }
    
    ComponentArray* componentArray = objectArchetype->GetComponentArray(componentArrayName_);

    if (componentArray == nullptr)
    {
      return false;
    }

    oldValue_ = componentArray->GetRTTRValue(0);
    componentArray->SetRTTRValue(newValue_, 0);

    return true;
  }

  void EditComponentArray::Undo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);
    ObjectArchetype* objectArchetype = poolArchetype->GetObjectArchetype(objectName_);
    ComponentArray* componentArray = objectArchetype->GetComponentArray(componentArrayName_);

    componentArray->SetRTTRValue(oldValue_, 0);
  }

  void EditComponentArray::Redo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);
    ObjectArchetype* objectArchetype = poolArchetype->GetObjectArchetype(objectName_);
    ComponentArray* componentArray = objectArchetype->GetComponentArray(componentArrayName_);

    componentArray->SetRTTRValue(newValue_, 0);
  }
}