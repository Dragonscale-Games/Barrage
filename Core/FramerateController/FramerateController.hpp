/* ======================================================================== */
/*!
 * \file            FramerateController.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Controls the game's FPS.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef FramerateController_BARRAGE_H
#define FramerateController_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <chrono>

struct GLFWwindow;

namespace Barrage
{ 
  //! Controls the game's FPS
  class FramerateController
  {
    public:
      enum class FpsMode
      {
        FPS_60,
        FPS_120,
        FPS_240
      };

      FramerateController();

      void Initialize(GLFWwindow* window, FpsMode fpsMode = FpsMode::FPS_60);

      void StartFrame();

      void EndFrame();

      void SetFPSMode(FpsMode fpsMode);

      void SetVsync(bool useVsync);

      long long DT();

      long long Accumulator();

      unsigned ConsumeTicks();
      
    private:
      void EndFrameBusyWait();

      void EndFrameSleep();

      void EndFrameVsync();

    private:
      GLFWwindow* window_; //!< Handle to the game window
      std::chrono::steady_clock::time_point frameStart_;
      std::chrono::steady_clock::time_point frameEnd_;
      long long minimumFrameTime_;
      long long accumulator_;
      long long dt_;
      bool usingVsync_;

      static const long long TICK_TIME = 4200;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // FramerateController_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////