/* ======================================================================== */
/*!
 * \file            FramerateController.hpp
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

 ////////////////////////////////////////////////////////////////////////////////
#ifndef FramerateController_BARRAGE_H
#define FramerateController_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <chrono>

struct GLFWwindow;

typedef std::chrono::steady_clock::time_point TimePoint;

namespace Barrage
{ 
  //! Controls the game's FPS
  class FramerateController
  {
    public:
      //! The values the fps can be capped at
      enum class FpsCap
      {
        FPS_60,
        FPS_120,
        NO_CAP
      };

      /**************************************************************/
      /*!
        \brief
          Default constructor.
      */
      /**************************************************************/
      FramerateController();

      /**************************************************************/
      /*!
        \brief
          Initializes the framerate controller. 

        \param window
          Handle to the game window.

        \param fpsCap
          The maximum number of frames per second.

        \param useVsync
          If true, vsync is turned on. If false, vsync is turned off.
      */
      /**************************************************************/
      void Initialize(GLFWwindow* window, FpsCap fpsCap, bool useVsync);

      /**************************************************************/
      /*!
        \brief
          Should be called once per frame before all other logic has
          run.
      */
      /**************************************************************/
      void StartFrame();

      /**************************************************************/
      /*!
        \brief
          Should be called once per frame after all other logic has
          run. Blocks until the minimum frame time has been reached.

          For maximum accuracy, the next frame's FrameStart() call
          should be directly after the current frame's EndFrame() call.
      */
      /**************************************************************/
      void EndFrame();

      /**************************************************************/
      /*!
        \brief
          Sets the framerate cap for the controller. EndFrame() will
          block until the actual frame time surpasses the minimum
          frame time at a given FPS.

        \param fpsCap
          The maximum framerate the game will run at. 
      */
      /**************************************************************/
      void SetFpsCap(FpsCap fpsCap);

      /**************************************************************/
      /*!
        \brief
          Allows vsync to be turned on or off.

        \param useVsync
          If true, vsync is turned on. If false, vsync is turned off.
      */
      /**************************************************************/
      void SetVsync(bool useVsync);

      /**************************************************************/
      /*!
        \brief
          Gets the amount of time elapsed last frame in microseconds.

        \return
          Returns the amount of time elapsed last frame in microseconds.
      */
      /**************************************************************/
      long long DT();

      /**************************************************************/
      /*!
        \brief
          Provides the number of ticks since the last time this
          function was called.

        \return
          Returns the number of ticks since the last time this
          function was called.
      */
      /**************************************************************/
      unsigned ConsumeTicks();
      
    private:
      /**************************************************************/
      /*!
        \brief
          Used to end a frame when using the busy wait method. It's
          the most accurate way to specify frame time, and provides 
          smooth gameplay with low input lag. However, maxes out CPU 
          usage.
      */
      /**************************************************************/
      void EndFrameBusyWait();

      /**************************************************************/
      /*!
        \brief
          Used to end a frame when using the thread sleep method. Low
          CPU usage, but choppy and inaccurate. Used when the game
          window is minimized or unfocused. 
      */
      /**************************************************************/
      void EndFrameSleep();

      /**************************************************************/
      /*!
        \brief
          Used to end a frame when using the vsync method. Low CPU
          usage and accurate, but can cause input lag and choppiness.
      */
      /**************************************************************/
      void EndFrameVsync();

    private:
      GLFWwindow* window_;         //!< Handle to the game window
      TimePoint frameStart_;       //!< Time when a frame starts
      TimePoint frameEnd_;         //!< Time when a frame ends
      long long minimumFrameTime_; //!< Frames are made to be at least this long when vsync is off
      long long accumulator_;      //!< Used to track excess time when dt is longer than TICK_TIME (in microseconds)
      long long dt_;               //!< The amount of time last frame took (in microseconds)
      bool usingVsync_;            //!< Keeps track of whether user is using vsync

      static const long long DT_60HZ = 16800;                            //!< Microseconds per frame at 60fps (slightly longer)
      static const long long TICKS_PER_FRAME_60HZ = 2;                   //!< Ticks per frame at 60fps (generally a power of 2)
      static const long long TICK_TIME = DT_60HZ / TICKS_PER_FRAME_60HZ; //!< Microseconds per tick
      static const long long TICK_EPSILON = 800;                         //!< Allowed error in time measurement (+/-)
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // FramerateController_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////