/* ======================================================================== */
/*!
 * \file            ObjectManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The main point of contact for game object manipulation in the engine.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "ObjectManager.hpp"
#include "Spaces/Space.hpp"

namespace Barrage
{
  ObjectManager::ObjectManager(Space& space) :
    pools_(),
    systemManager_(space)
  {
  }

  void ObjectManager::Update()
  {
    systemManager_.Update();
  }

  void ObjectManager::SubscribePools()
  {
    for (auto it = pools_.begin(); it != pools_.end(); ++it)
    {
      Pool& pool = it->second;
      systemManager_.Subscribe(&pool);
    }
  }

  void ObjectManager::CreatePool(const PoolArchetype& archetype)
  {
    pools_.emplace(archetype.GetName(), Pool(archetype));
  }

  void ObjectManager::DeleteAllPools()
  {
    for (auto it = pools_.begin(); it != pools_.end(); ++it)
    {
      Pool& pool = it->second;
      systemManager_.Unsubscribe(&pool);
    }

    pools_.clear();
  }
}