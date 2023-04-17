/* ======================================================================== */
/*!
 * \file            DeletePool.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Removes a pool archetype from the scene and the archetype manager.
 */
 /* ======================================================================== */

#include "DeletePool.hpp"
#include <Engine/Engine.hpp>
#include <Editor/Editor.hpp>

namespace Barrage
{
  DeletePool::DeletePool(const std::string& sceneName, const std::string& poolName) :
    Command("Deleted pool. (" + poolName + ")"),
    sceneName_(sceneName),
    poolName_(poolName),
    undoIndex_(0),
    undoPoolArchetype_(nullptr)
  {
  }

  DeletePool::~DeletePool()
  {
    delete undoPoolArchetype_;
  }

  bool DeletePool::Execute()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    if (scene == nullptr)
    {
      return false;
    }

    undoPoolArchetype_ = scene->ExtractPoolArchetype(poolName_, &undoIndex_);

    if (undoPoolArchetype_ == nullptr)
    {
      return false;
    }

    if (Editor::Instance->Data().selectedPool_ == poolName_)
    {
      Editor::Instance->Data().selectedPool_ = std::string();
    }

    return true;
  }

  void DeletePool::Undo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    scene->AddPoolArchetype(undoPoolArchetype_, &undoIndex_);
    undoPoolArchetype_ = nullptr;
  }

  void DeletePool::Redo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    undoPoolArchetype_ = scene->ExtractPoolArchetype(poolName_, &undoIndex_);

    if (Editor::Instance->Data().selectedPool_ == poolName_)
    {
      Editor::Instance->Data().selectedPool_ = std::string();
    }
  }
}