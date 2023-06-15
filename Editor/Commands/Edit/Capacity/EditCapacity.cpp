/* ======================================================================== */
/*!
 * \file            EditCapacity.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Edits a pool archetype's capacity.
 */
 /* ======================================================================== */

#include "EditCapacity.hpp"
#include <Editor.hpp>

namespace Barrage
{
  EditCapacity::EditCapacity(
    const std::string& sceneName,
    const std::string& poolName,
    unsigned newCapacity,
    bool chainUndo) :
    Command("Changed capacity of " + poolName + ".", chainUndo),
    sceneName_(sceneName),
    poolName_(poolName),
    newValue_(newCapacity),
    oldValue_(0)
  {
  }

  bool EditCapacity::Execute()
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

    oldValue_ = poolArchetype->GetCapacity();
    poolArchetype->SetCapacity(newValue_);

    return true;
  }

  void EditCapacity::Undo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    poolArchetype->SetCapacity(oldValue_);
  }

  void EditCapacity::Redo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    poolArchetype->SetCapacity(newValue_);
  }
}