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

     static void AddDrawSample(long long sample);

    private:
      static const size_t MAX_SAMPLES = 100;
      
      static long long frameSamples_[MAX_SAMPLES];
      static long long maxFrameSample_;
      static size_t currentFrameSampleIndex_;
      static size_t numFrameSamples_;
      static long long drawSamples_[MAX_SAMPLES];
      static long long maxDrawSample_;
      static size_t currentDrawSampleIndex_;
      static size_t numDrawSamples_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // PerformanceWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////