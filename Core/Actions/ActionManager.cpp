/* ======================================================================== */
/*!
 * \file            ActionManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here>

 */
 /* ======================================================================== */

#include "stdafx.h"
#include "ActionManager.hpp"
#include "Engine/Engine.hpp"

namespace Barrage
{
  ActionManager::ActionManager() :
    currentTick_(0),
    mode_(Mode::Default),
    previousState_(),
    currentState_(),
    replayData_(),
    replayPos_(0),
    actionKeyMap_()
  {
    replayData_.reserve(10000);
  }

  void ActionManager::MapActionKey(const ACTION& action, KEY key)
  {
    actionKeyMap_[action] = key;

    if (action >= previousState_.size())
    {
      previousState_.resize(action + 1, false);
      currentState_.resize(action + 1, false);
    }
  }

  void ActionManager::SetMode(Mode newMode)
  {
    mode_ = newMode;

    Reset();
  }

  void ActionManager::Reset()
  {
    currentTick_ = 0;
    
    for (size_t i = 0; i < previousState_.size(); ++i)
    {
      previousState_[i] = false;
    }

    for (size_t i = 0; i < currentState_.size(); ++i)
    {
      currentState_[i] = false;
    }

    if (mode_ == Mode::Record)
    {
      replayData_.clear();
    }
    else
    {
      replayPos_ = 0;
    }
  }

  void ActionManager::Update()
  {
    previousState_ = currentState_;
    
    if (mode_ == Mode::Replay)
    {
      GetReplayInput();
    }
    else
    {
      GetNormalInput();
    }

    currentTick_++;
  }

  bool ActionManager::ActionTriggered(ACTION action) const
  {
    if (action < previousState_.size() && action < currentState_.size())
    {
      return !previousState_[action] && currentState_[action];
    }
    else
    {
      return false;
    }
  }

  bool ActionManager::ActionIsDown(ACTION action) const
  {
    if (action < currentState_.size())
    {
      return currentState_[action];
    }
    else
    {
      return false;
    }
  }

  bool ActionManager::ActionReleased(ACTION action) const
  {
    if (action < previousState_.size() && action < currentState_.size())
    {
      return previousState_[action] && !currentState_[action];
    }
    else
    {
      return false;
    }
  }

  void ActionManager::GetNormalInput()
  {
    for (size_t i = 0; i < currentState_.size(); ++i)
    {
      currentState_[i] = false;
    }

    InputManager& input_manager = Engine::Instance->Input();

    for (auto it = actionKeyMap_.begin(); it != actionKeyMap_.end(); ++it)
    {
      ACTION action = it->first;
      KEY key = it->second;

      currentState_[action] = input_manager.KeyIsDown(key);

      if (mode_ == Mode::Record && currentState_[action] != previousState_[action])
      {
        StateChange state_change;

        state_change.tick_ = currentTick_;
        state_change.action_ = action;

        replayData_.push_back(state_change);
      }
    }
  }

  void ActionManager::GetReplayInput()
  {
    while (replayPos_ < replayData_.size() && replayData_[replayPos_].tick_ == currentTick_)
    {
      ACTION action = replayData_[replayPos_].action_;

      if (action < currentState_.size())
      {
        currentState_[action] = !currentState_[action];
      }

      replayPos_++;
    }
  }
}