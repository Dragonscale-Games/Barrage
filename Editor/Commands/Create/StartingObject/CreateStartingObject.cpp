/* ======================================================================== */
/*!
 * \file            CreateStartingObject.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Creates a new object archetype and adds it as a starting object to a pool
   in the scene.
 */
 /* ======================================================================== */

#include "CreateStartingObject.hpp"
#include "Editor.hpp"

namespace Barrage
{
  CreateStartingObject::CreateStartingObject(
    const std::string& sceneName, 
    const std::string& poolName) :
    Command("New starting object created in " + poolName + "."),
    sceneName_(sceneName),
    poolName_(poolName),
    startingObjectName_()
  {
  }

  bool CreateStartingObject::Execute()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);

    if (scene == nullptr || scene->poolArchetypes_.count(poolName_) == 0)
    {
      return false;
    }

    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    if (poolArchetype.startingObjects_.size() >= poolArchetype.capacity_)
    {
      LogWidget::AddEntry("Error: Could not create object (" + poolName_ + " is full).");
      return false;
    }

    unsigned counter = 0;

    do {
      startingObjectName_ = "Object";

      if (counter)
      {
        startingObjectName_ += " ";
        startingObjectName_ += std::to_string(counter);
      }
      
      counter++;

    } while (poolArchetype.startingObjects_.count(startingObjectName_));

    poolArchetype.startingObjects_.emplace(startingObjectName_, ObjectArchetype(startingObjectName_, poolArchetype.componentArrayNames_));
    
    return true;
  }

  void CreateStartingObject::Undo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    poolArchetype.startingObjects_.erase(startingObjectName_);

    if (Editor::Get().Data().selectedStartingObject_ == startingObjectName_)
    {
      Editor::Get().Data().selectedStartingObject_ = std::string();
    }
  }

  void CreateStartingObject::Redo()
  {
    Scene* scene = Engine::Get().Scenes().GetScene(sceneName_);
    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(poolName_);

    poolArchetype.startingObjects_.emplace(startingObjectName_, ObjectArchetype(startingObjectName_, poolArchetype.componentArrayNames_));
  }
}