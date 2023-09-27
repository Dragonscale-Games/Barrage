/* ======================================================================== */
/*!
 * \file            ActionManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Turns inputs into game actions. Also handles recording and replaying
   actions for game replays.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef ActionManager_BARRAGE_H
#define ActionManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Input/InputManager.hpp"

#include <cstdint>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>

namespace Barrage
{
  typedef uint32_t ACTION;
  typedef std::unordered_map <ACTION, KEY> ActionKeyUmap;

  //! Turns inputs into game actions and handles game recording/replaying
  class ActionManager
  {
    public:
      enum class Mode
      {
        Default,
        Record,
        Replay
      };

      struct StateChange
      {
        uint32_t tick_;
        uint32_t action_;
      };

      ActionManager();

      void MapActionKey(ACTION action, KEY key);

      void SetMode(Mode newMode);

      void Reset();

      void Update();

      bool ActionTriggered(ACTION action) const;

      bool ActionIsDown(ACTION action) const;

      bool ActionReleased(ACTION action) const;

    private:
      void GetNormalInput();

      void GetReplayInput();

    private:
      uint32_t currentTick_;
      Mode mode_;
      std::vector<bool> previousState_;
      std::vector<bool> currentState_;
      std::vector<StateChange> replayData_;
      size_t replayPos_;
      ActionKeyUmap actionKeyMap_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // ActionManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////