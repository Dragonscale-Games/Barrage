/* ======================================================================== */
/*!
 * \file            GameStateManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Manages the current game state.
 */
/* ======================================================================== */

#include "stdafx.h"
#include "GameStateManager.hpp"

namespace Barrage
{
  GameStateManager::GameStateManager() :
    current_(nullptr, nullptr, nullptr),
    next_(nullptr, nullptr, nullptr),
    stateIsRunning_(false)
  {
  }

  void GameStateManager::SetGameState(GameState state)
  {
    // make sure new state at least has an update function
    if (state.update_)
    {
      // if the new state is different from the old state, queue it as the next state
      if (state != current_)
      {
        next_ = state;
      }
      // if the new state is the same as the old state, queue a game state restart event
      else
      {
        // if the "next" game state's update function is nullptr, it's
        // interpreted as a game state restart event
        next_.update_ = nullptr;
      }

      stateIsRunning_ = true;
    }
  }

  void GameStateManager::Update()
  {
    // if a game state change or restart event is queued...
    if (GameStateIsChanging())
    {
      // if it's a restart event...
      if (GameStateIsRestarting())
      {
        // clear the restart event
        next_ = current_;

        // call the restarting game state's exit function (if it exists)
        if (current_.exit_)
          current_.exit_();

        // call the restarting game state's enter function (if it exists)
        if (current_.enter_)
          current_.enter_();
      }
      // if it's a game state change event...
      else
      {
        // call the exit function of the game state we're leaving (if it exists)
        if (current_.exit_)
          current_.exit_();

        // move to the next game state
        current_ = next_;

        // call the enter function of the game state we're entering (if it exists)
        if (current_.enter_)
          current_.enter_();
      }
    }
    
    // if a game state is running, call its update function no matter what
    if (current_.update_)
      current_.update_();

    // if a quit command was received, shut the current game state down and clear the manager
    if (!stateIsRunning_)
    {
      if (current_.exit_)
        current_.exit_();

      current_ = GameState(nullptr, nullptr, nullptr);
      next_ = GameState(nullptr, nullptr, nullptr);
    }
  }

  void GameStateManager::QuitGameState()
  {
    stateIsRunning_ = false;
  }

  void GameStateManager::Shutdown()
  {
    if (current_.exit_)
      current_.exit_();

    current_ = GameState(nullptr, nullptr, nullptr);
    next_ = GameState(nullptr, nullptr, nullptr);
  }

  bool GameStateManager::GameStateIsRunning()
  {
    return stateIsRunning_;
  }

  bool GameStateManager::GameStateIsChanging() const
  {
    return current_ != next_;
  }

  bool GameStateManager::GameStateIsRestarting() const
  {
    // if the "next" game state's update function is nullptr, it's
    // interpreted as a game state restart event
    return next_.update_ == nullptr;
  }
}