/* ======================================================================== */
/*!
 * \file            PerformanceWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Widget for displaying performance metrics for current game.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef PerformanceWidget_BARRAGE_H
#define PerformanceWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <imgui/imgui.h>
#include <vector>

namespace Barrage
{
  //! Displays a log window
  class PerformanceWidget
  {
    public:
     /**************************************************************/
     /*!
       \brief
         Adds the widget to the window.
     */
     /**************************************************************/
     static void Use();

     static void Reset();

     static void AddFrameSample(long long sample);

    private:
      static const size_t MAX_FRAME_SAMPLES = 100;
      
      static long long frameSamples_[MAX_FRAME_SAMPLES];
      static long long maxSample_;
      static size_t currentIndex_;
      static size_t numSamples_;

  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // PerformanceWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////