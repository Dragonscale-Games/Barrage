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
  struct ActionInfo
  {
    int key_;
    bool isDown_;
    bool triggered_;
    bool released_;

    ActionInfo();
  };

  struct ReplayState
  {
    uint32_t tick_;
    unsigned char action_;
    bool isDown_;
    bool triggered_;
    bool released_;

    ReplayState(uint32_t tick, unsigned char action, ActionInfo info);
  };

  using ActionInfoUmap = std::unordered_map<unsigned char, ActionInfo>;

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

      ActionManager();

      void MapActionKey(unsigned char action, int key);

      void SetMode(Mode newMode);

      void Reset();

      void Update();

      bool ActionTriggered(unsigned char action) const;

      bool ActionIsDown(unsigned char action) const;

      bool ActionReleased(unsigned char action) const;

    private:
      void GetNormalInput();

      void GetReplayInput();

    private:
      ActionInfoUmap actionInfoMap_;
      uint32_t currentTick_;
      Mode mode_;
      std::vector<ReplayState> replayData_;
      size_t replayPos_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // ActionManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////