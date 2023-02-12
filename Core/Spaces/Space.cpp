/* ======================================================================== */
/*!
 * \file            Space.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A space is a collection of scenes and game objects. Each space represents
   a unique simulation.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "Space.hpp"
#include "Engine/Engine.hpp"

namespace Barrage
{
  Space::Space() :
    actionManager_(),
    objectManager_(*this),
    rng_(),
    paused_(false),
    visible_(true)
  {
  }

  void Space::Update()
  {
    if (!paused_)
    {
      actionManager_.Update();
      objectManager_.Update();
    }
  }

  void Space::Draw()
  {
    if (visible_)
    {
      objectManager_.Draw();
    }
  }

  ActionManager& Space::GetActionManager()
  {
    return actionManager_;
  }

  ObjectManager& Space::GetObjectManager()
  {
    return objectManager_;
  }

  Random& Space::GetRNG()
  {
    return rng_;
  }

  void Space::SetScene(const std::string& name)
  {
    Scene* new_scene = Engine::Instance->Scenes().GetScene(name);

    if (new_scene == nullptr)
      return;
    
    objectManager_.DeleteAllPools();

    const PoolInfoMap& starting_pools = new_scene->startingPools_;

    for (auto it = starting_pools.begin(); it != starting_pools.end(); ++it)
    {
      objectManager_.CreatePoolAndObjects(it->second);
    }

    rng_.SetSeed();
  }

  void Space::SetPaused(bool isPaused)
  {
    paused_ = isPaused;
  }

  void Space::SetVisible(bool isVisible)
  {
    visible_ = isVisible;
  }

  bool Space::IsPaused() const
  {
    return paused_;
  }

  bool Space::IsVisible() const
  {
    return visible_;
  }
}