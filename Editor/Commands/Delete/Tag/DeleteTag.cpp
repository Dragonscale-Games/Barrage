/* ======================================================================== */
/*!
 * \file            DeleteTag.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Removes a tag from a pool archetype.
 */
 /* ======================================================================== */

#include "DeleteTag.hpp"
#include <Editor.hpp>

namespace Barrage
{
  DeleteTag::DeleteTag(
    const std::string& sceneName,
    const std::string& poolName,
    const std::string_view& tag) :
    Command("Removed \"" + std::string(tag) + "\" tag from " + poolName + "."),
    sceneName_(sceneName),
    poolName_(poolName),
    tag_(tag),
    undoIndex_(0)
  {
  }

  bool DeleteTag::Execute()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    if (scene == nullptr)
    {
      return false;
    }

    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    if (poolArchetype == nullptr || !poolArchetype->HasTag(tag_))
    {
      return false;
    }

    poolArchetype->RemoveTag(tag_, &undoIndex_);

    return true;
  }

  void DeleteTag::Undo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    poolArchetype->AddTag(tag_, &undoIndex_);
  }

  void DeleteTag::Redo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    poolArchetype->RemoveTag(tag_, &undoIndex_);
  }
}
