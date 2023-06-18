/* ======================================================================== */
/*!
 * \file            RenamePool.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Renames a pool.
 */
 /* ======================================================================== */

#include "RenamePool.hpp"
#include <Editor.hpp>

namespace Barrage
{
  RenamePool::RenamePool(
    const std::string& sceneName,
    const std::string& poolName,
    const std::string& newName) :
    Command("Renamed pool \"" + poolName + "\" to \"" + newName + "\"."),
    sceneName_(sceneName),
    poolName_(poolName),
    newName_(newName)
  {
  }

  bool RenamePool::Execute()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    
    if (scene == nullptr)
    {
      return false;
    }
    
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);
    
    if (poolArchetype == nullptr || scene->HasPool(newName_))
    {
      return false;
    }
    
    poolArchetype->SetName(newName_);
    
    EditorData& editorData = Editor::Instance->Data();
    if (editorData.selectedPool_ == poolName_)
    {
      editorData.selectedPool_ = newName_;
    }

    return true;
  }

  void RenamePool::Undo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(newName_);

    poolArchetype->SetName(poolName_);

    EditorData& editorData = Editor::Instance->Data();
    if (editorData.selectedPool_ == newName_)
    {
      editorData.selectedPool_ = poolName_;
    }
  }

  void RenamePool::Redo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    poolArchetype->SetName(newName_);

    EditorData& editorData = Editor::Instance->Data();
    if (editorData.selectedPool_ == poolName_)
    {
      editorData.selectedPool_ = newName_;
    }
  }
}