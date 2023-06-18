/* ======================================================================== */
/*!
 * \file            RenameObject.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Renames an object.
 */
 /* ======================================================================== */

#include "RenameObject.hpp"
#include <Editor.hpp>

namespace Barrage
{
  RenameObject::RenameObject(
    const std::string& sceneName,
    const std::string& poolName,
    const std::string& objectName,
    const std::string& newName) :
    Command("Renamed object \"" + objectName + "\" to \"" + newName + "\"."),
    sceneName_(sceneName),
    poolName_(poolName),
    objectName_(objectName),
    newName_(newName)
  {
  }
  
  bool RenameObject::Execute()
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

    if (objectArchetype == nullptr || poolArchetype->HasObjectArchetype(newName_))
    {
      return false;
    }

    objectArchetype->SetName(newName_);

    EditorData& editorData = Editor::Instance->Data();
    if (editorData.selectedObject_ == objectName_)
    {
      editorData.selectedObject_ = newName_;
    }

    return true;
  }
    
  void RenameObject::Undo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);
    ObjectArchetype* objectArchetype = poolArchetype->GetObjectArchetype(newName_);

    objectArchetype->SetName(objectName_);

    EditorData& editorData = Editor::Instance->Data();
    if (editorData.selectedObject_ == newName_)
    {
      editorData.selectedObject_ = objectName_;
    }
  }

  void RenameObject::Redo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);
    ObjectArchetype* objectArchetype = poolArchetype->GetObjectArchetype(objectName_);

    objectArchetype->SetName(newName_);

    EditorData& editorData = Editor::Instance->Data();
    if (editorData.selectedObject_ == objectName_)
    {
      editorData.selectedObject_ = newName_;
    }
  }
}