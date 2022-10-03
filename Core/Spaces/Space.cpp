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

namespace Barrage
{
  Space::Space() :
    objectManager_(*this),
    scenes_(),
    paused_(false)
  {
  }

  Space::~Space()
  {
    for (auto it = scenes_.begin(); it != scenes_.end(); ++it)
    {
      delete it->second;
    }
  }

  void Space::Update()
  {
    if (!paused_)
      objectManager_.Update();
  }

  void Space::Draw()
  {
    objectManager_.Draw();
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

  void Space::AddScene(const std::string& name, Scene* scene)
  {
    if (scenes_.find(name) == scenes_.end())
    {
      scenes_[name] = scene;
    }
    else
    {
      delete scene;
    }
  }

  void Space::SetScene(const std::string name)
  {
    if (scenes_.find(name) == scenes_.end())
      return;

    objectManager_.DeleteAllPools();
    
    Scene* scene = scenes_.at(name);
    const std::vector<PoolInfo>& starting_pools = scene->startingPools_;

    for (auto it = starting_pools.begin(); it != starting_pools.end(); ++it)
    {
      objectManager_.CreatePoolAndObjects(*it);
    }

    rng_.SetSeed(scene->rngSeed_);
  }

  void Space::SetPaused(bool isPaused)
  {
    paused_ = isPaused;
  }

  bool Space::IsPaused()
  {
    return paused_;
  }
}