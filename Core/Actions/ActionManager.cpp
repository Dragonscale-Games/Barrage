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
#include "Engine.hpp"

namespace Barrage
{
  ActionInfo::ActionInfo() :
    key_(0),
    isDown_(false),
    triggered_(false),
    released_(false)
  {
  }

  ReplayState::ReplayState(uint32_t tick, unsigned char action, ActionInfo info) :
    tick_(tick),
    action_(action),
    isDown_(info.isDown_),
    triggered_(info.triggered_),
    released_(info.released_)
  {
  }
  
  ActionManager::ActionManager() :
    actionInfoMap_(),
    currentTick_(0),
    mode_(Mode::Default),
    replayData_(),
    replayPos_(0)
  {
    replayData_.reserve(10000);
  }

  void ActionManager::MapActionKey(unsigned char action, int key)
  {
    actionInfoMap_[action].key_ = key;
  }

  void ActionManager::SetMode(Mode newMode)
  {
    mode_ = newMode;

    Reset();
  }

  void ActionManager::Reset()
  {
    currentTick_ = 0;

    for (auto it = actionInfoMap_.begin(); it != actionInfoMap_.end(); ++it)
    {
      it->second.isDown_ = false;
      it->second.triggered_ = false;
      it->second.released_ = false;
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

  bool ActionManager::ActionTriggered(unsigned char action) const
  {
    if (actionInfoMap_.count(action))
    {
      return actionInfoMap_.at(action).triggered_;
    }
    else
    {
      return false;
    }
  }

  bool ActionManager::ActionIsDown(unsigned char action) const
  {
    if (actionInfoMap_.count(action))
    {
      return actionInfoMap_.at(action).isDown_;
    }
    else
    {
      return false;
    }
  }

  bool ActionManager::ActionReleased(unsigned char action) const
  {
    if (actionInfoMap_.count(action))
    {
      return actionInfoMap_.at(action).released_;
    }
    else
    {
      return false;
    }
  }

  void ActionManager::GetNormalInput()
  {
    InputManager& input = Engine::Get().Input();

    for (auto it = actionInfoMap_.begin(); it != actionInfoMap_.end(); ++it)
    {
      unsigned char action = it->first;
      ActionInfo& actionInfo = it->second;

      bool isDown = input.KeyIsDown(actionInfo.key_);
      bool triggered = input.KeyTriggered(actionInfo.key_);
      bool released = input.KeyReleased(actionInfo.key_);

      bool recordInput = (actionInfo.isDown_ != isDown) || triggered || released;
      
      actionInfo.isDown_ = isDown;
      actionInfo.triggered_ = triggered;
      actionInfo.released_ = released;

      if (mode_ == Mode::Record && recordInput)
      {
        replayData_.push_back(ReplayState(currentTick_, action, actionInfo));
      }
    }
  }

  void ActionManager::GetReplayInput()
  {
    for (auto it = actionInfoMap_.begin(); it != actionInfoMap_.end(); ++it)
    {
      it->second.triggered_ = false;
      it->second.released_ = false;
    }
    
    while (replayPos_ < replayData_.size() && replayData_[replayPos_].tick_ == currentTick_)
    {
      ReplayState& state = replayData_[replayPos_];

      if (actionInfoMap_.count(state.action_))
      {
        ActionInfo& actionInfo = actionInfoMap_.at(state.action_);

        actionInfo.isDown_ = state.isDown_;
        actionInfo.triggered_ = state.triggered_;
        actionInfo.released_ = state.released_;
      }

      replayPos_++;
    }
  }
}