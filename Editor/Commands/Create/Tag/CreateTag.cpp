/* ======================================================================== */
/*!
 * \file            CreateTag.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Adds a tag to a pool archetype.
 */
 /* ======================================================================== */

#include "CreateTag.hpp"
#include <Editor.hpp>

namespace Barrage
{
  CreateTag::CreateTag(
    const std::string& sceneName,
    const std::string& poolName,
    const std::string_view& tag) :
    Command("Added \"" + std::string(tag) + "\" tag to " + poolName + "."),
    sceneName_(sceneName),
    poolName_(poolName),
    tag_(tag)
  {
  }

  bool CreateTag::Execute()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);

    if (scene == nullptr)
    {
      return false;
    }

    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    if (poolArchetype == nullptr || poolArchetype->HasTag(tag_))
    {
      return false;
    }

    poolArchetype->AddTag(tag_);

    return true;
  }
  
  void CreateTag::Undo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    poolArchetype->RemoveTag(tag_);
  }
  
  void CreateTag::Redo()
  {
    Scene* scene = Engine::Instance->Scenes().GetScene(sceneName_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(poolName_);

    poolArchetype->AddTag(tag_);
  }
}