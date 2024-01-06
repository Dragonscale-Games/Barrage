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
#include "Engine.hpp"

namespace Barrage
{
  Space::Space() :
    actionManager_(),
    objectManager_(*this),
    rng_(),
    paused_(false),
    visible_(true),
    allowSceneChangesDuringUpdate_(true),
    isUpdating_(false),
    queuedScene_()
  {
  }

  void Space::Update()
  {
    if (!paused_)
    {
      isUpdating_ = true;
      actionManager_.Update();
      objectManager_.Update();
      isUpdating_ = false;

      if (!queuedScene_.empty())
      {
        SetScene(queuedScene_);
        queuedScene_.clear();
      }
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
    if (isUpdating_)
    {
      if (allowSceneChangesDuringUpdate_)
      {
        queuedScene_ = name;
      }

      return;
    }

    Scene* new_scene = Engine::Get().Scenes().GetScene(name);

    if (new_scene == nullptr)
    {
      return;
    }
      
    objectManager_.DeleteAllPools();

    const PoolArchetypeMap& starting_pools = new_scene->GetPoolArchetypes();

    for (auto it = starting_pools.begin(); it != starting_pools.end(); ++it)
    {
      objectManager_.CreatePool(it->second);
    }

    objectManager_.SubscribePools();

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

  void Space::AllowSceneChangesDuringUpdate(bool allow)
  {
    allowSceneChangesDuringUpdate_ = allow;
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