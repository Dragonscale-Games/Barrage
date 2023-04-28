/* ======================================================================== */
/*!
 * \file            CreateObject.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Creates a new (empty) object archetype and adds that object to a pool
   in the scene.
 */
 /* ======================================================================== */

#include "CreateObject.hpp"
#include "Editor/Editor.hpp"

namespace Barrage
{
  CreateObject::CreateObject(const std::string& sceneName, const std::string& poolName) :
    Command("New object created in " + poolName + "."),
    sceneName_(sceneName),
    poolName_(poolName),
    objectName_(),
    redoArchetype_(nullptr)
  {
  }

  CreateObject::~CreateObject()
  {
    delete redoArchetype_;
  }

  bool CreateObject::Execute()
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

    if (poolArchetype->GetStartingObjects().size() >= poolArchetype->GetCapacity())
    {
      LogWidget::AddEntry("Error: Could not create object (" + poolName_ + " is full).");
      return false;
    }

    if (objectName_.empty())
    {
      unsigned counter = 0;

      do {
        objectName_ = "Object";

        if (counter)
        {
          objectName_ += " ";
          objectName_ += std::to_string(counter);
        }
        
        counter++;

      } while (poolArchetype->HasObjectArchetype(objectName_));
    }

    poolArchetype->AddStartingObject(new ObjectArchetype(objectName_, poolArchetype->GetComponentArrayNames()));

    return true;
  }

  void CreateObject::Undo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    redoArchetype_ = poolArchetype->ExtractStartingObject(objectName_);

    if (Editor::Instance->Data().selectedObject_ == objectName_)
    {
      Editor::Instance->Data().selectedObject_ = std::string();
    }
  }

  void CreateObject::Redo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    poolArchetype->AddStartingObject(redoArchetype_);
    redoArchetype_ = nullptr;
  }
}