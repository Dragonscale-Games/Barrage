/* ======================================================================== */
/*!
 * \file            FramerateController.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Controls the game's tick rate and frame rate. The tick rate of a game is
   the number of times per second the game simulation is updated. The frame
   rate is the number of times per second input is polled and the game is
   rendered.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "FramerateController.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <thread>

namespace Barrage
{
  FramerateController::FramerateController() :
    frameStart_(),
    frameEnd_(),
    minimumFrameTime_(0),
    accumulator_(0),
    dt_(0),
    usingVsync_(true)
  {
  }

  void FramerateController::Initialize(FpsCap fpsCap, bool useVsync)
  {
    SetVsync(useVsync);
    SetFpsCap(fpsCap);
    frameStart_ = std::chrono::high_resolution_clock::now();
  }

  void FramerateController::StartFrame()
  {
    frameStart_ = std::chrono::high_resolution_clock::now();
  }

  void FramerateController::EndFrame(bool minimizeCpuUsage)
  {
    if (usingVsync_)
    {
      EndFrameVsync();
    }
    else if (minimizeCpuUsage)
    {
      EndFrameSleep(); 
    }
    else
    {
      EndFrameBusyWait();
    }

    // if dt is a nonzero number of ticks within the error margin, round it to that many ticks
    // this allows better syncing when monitors refresh at a rate slightly faster or slower than a multiple of 60Hz
    if (dt_ % TICK_TIME < TICK_EPSILON && dt_ >= TICK_TIME)
    {
      dt_ -= dt_ % TICK_TIME;
    }
    else if (dt_ % TICK_TIME > TICK_TIME - TICK_EPSILON)
    {
      dt_ += TICK_TIME - (dt_ % TICK_TIME);
    }

    accumulator_ += dt_;
  }

  void FramerateController::SetFpsCap(FpsCap fpsCap)
  {
    switch (fpsCap)
    {
      case FpsCap::FPS_60:
        minimumFrameTime_ = DT_60HZ;
        break;

      case FpsCap::FPS_120:
        minimumFrameTime_ = DT_60HZ / 2;
        break;

      default:
        minimumFrameTime_ = 0;
        break;
    }
  }

  void FramerateController::SetVsync(bool enable)
  {
    if (enable)
    {
      usingVsync_ = true;
      glfwSwapInterval(1);
    }
    else
    {
      usingVsync_ = false;
      glfwSwapInterval(0);
    }
  }

  long long FramerateController::DT()
  {
    return dt_;
  }

  unsigned FramerateController::ConsumeTicks()
  {
    unsigned num_ticks = static_cast<unsigned>(accumulator_ / TICK_TIME);

    accumulator_ = accumulator_ % TICK_TIME;

    if (num_ticks > TICKS_PER_FRAME_60HZ)
    {
      num_ticks = TICKS_PER_FRAME_60HZ;
    }

    return num_ticks;
  }

  void FramerateController::EndFrameBusyWait()
  {
    std::chrono::microseconds duration;

    do {

      frameEnd_ = std::chrono::high_resolution_clock::now();
      duration = std::chrono::duration_cast<std::chrono::microseconds>(frameEnd_ - frameStart_);

    } while (duration.count() < minimumFrameTime_);

    dt_ = duration.count();
  }

  void FramerateController::EndFrameSleep()
  {
    frameEnd_ = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(frameEnd_ - frameStart_);

    while (duration.count() < minimumFrameTime_)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      
      frameEnd_ = std::chrono::high_resolution_clock::now();
      duration = std::chrono::duration_cast<std::chrono::microseconds>(frameEnd_ - frameStart_);
    }

    dt_ = duration.count();
  }

  void FramerateController::EndFrameVsync()
  {
    frameEnd_ = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(frameEnd_ - frameStart_);
    dt_ = duration.count();
  }
}