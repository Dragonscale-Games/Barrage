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
    if (newValue_ < 1)
    {
      LogWidget::AddEntry("Error: Cannot set pool's capacity below 1.");
      return false;
    }

    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);

    if (scene == nullptr || scene->poolArchetypes_.count(poolName_) == 0)
    {
      return false;
    }

    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    if (newValue_ < poolArchetype.startingObjects_.size())
    {
      LogWidget::AddEntry("Error: Cannot set pool's capacity below its number of starting objects.");
      return false;
    }

    oldValue_ = poolArchetype.capacity_;
    poolArchetype.capacity_ = newValue_;

    return true;
  }

  void EditCapacity::Undo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    poolArchetype.capacity_ = oldValue_;
  }

  void EditCapacity::Redo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    poolArchetype.capacity_ = newValue_;
  }
}