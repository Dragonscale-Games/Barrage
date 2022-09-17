/* ======================================================================== */
/*!
 * \file            FramerateController.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Controls the game's FPS.
 */
 /* ======================================================================== */

#include "FramerateController.hpp"

#include <thread>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Barrage
{
  FramerateController::FramerateController() :
    window_(nullptr),
    frameStart_(),
    frameEnd_(),
    minimumFrameTime_(0),
    accumulator_(0),
    dt_(0),
    usingVsync_(true)
  {
    glfwSwapInterval(1);
  }

  void FramerateController::Initialize(GLFWwindow* window, FpsMode fpsMode)
  {
    window_ = window;
    SetFPSMode(fpsMode);
    StartFrame(); // for safety, so the frame start time is never uninitialized
  }

  void FramerateController::StartFrame()
  {
    frameStart_ = std::chrono::high_resolution_clock::now();
  }

  void FramerateController::EndFrame()
  {
    if (usingVsync_)
      EndFrameVsync();
    else if (glfwGetWindowAttrib(window_, GLFW_FOCUSED))
      EndFrameBusyWait();
    else
      EndFrameSleep();

    if (dt_ >= TICK_TIME * 4)
      dt_ = TICK_TIME * 4;

    if (dt_ % TICK_TIME < 100)
      dt_ -= dt_ % TICK_TIME;

    accumulator_ += dt_;
  }

  void FramerateController::SetFPSMode(FpsMode fpsMode)
  {
    switch (fpsMode)
    {
      case FpsMode::FPS_60:
        minimumFrameTime_ = TICK_TIME * 4;
        break;

      case FpsMode::FPS_120:
        minimumFrameTime_ = TICK_TIME * 2;
        break;

      case FpsMode::FPS_240:
        minimumFrameTime_ = TICK_TIME;
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

  long long FramerateController::Accumulator()
  {
    return accumulator_;
  }

  unsigned FramerateController::ConsumeTicks()
  {
    unsigned num_ticks = 0;

    for (unsigned i = 0; i < 4; ++i)
    {
      if (accumulator_ >= TICK_TIME)
      {
        num_ticks++;
        accumulator_ -= TICK_TIME;
      }
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
      std::this_thread::sleep_for(std::chrono::microseconds(minimumFrameTime_ - duration.count()));
      
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