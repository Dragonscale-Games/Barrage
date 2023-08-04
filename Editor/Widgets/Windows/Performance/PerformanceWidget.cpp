/* ======================================================================== */
/*!
 * \file            PerformanceWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Widget for displaying performance metrics for current game.
 */
 /* ======================================================================== */

#include "PerformanceWidget.hpp"
#include <string>

namespace Barrage
{
  long long PerformanceWidget::frameSamples_[PerformanceWidget::MAX_FRAME_SAMPLES] = { 0 };
  long long PerformanceWidget::maxSample_ = 0;
  size_t PerformanceWidget::currentIndex_ = 0;
  size_t PerformanceWidget::numSamples_ = 0;
  
  void PerformanceWidget::Use()
  {
    float totalTime = 0;
    size_t numSamples = numSamples_ < MAX_FRAME_SAMPLES ? numSamples_ : MAX_FRAME_SAMPLES;
    for (size_t i = 0; i < MAX_FRAME_SAMPLES; ++i)
    {
      totalTime += frameSamples_[i];
    }

    long long averageTime = numSamples > 0 ? static_cast<long long>(totalTime / numSamples) : 0;

    ImGui::Begin("Performance");
    ImGui::Text("Frame time: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(averageTime).c_str());

    ImGui::Text("Max time:   ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(maxSample_).c_str());
    if (ImGui::Button("Reset max"))
    {
      maxSample_ = 0;
    }
    ImGui::End();
  }

  void PerformanceWidget::Reset()
  {
    maxSample_ = 0;
    currentIndex_ = 0;
    numSamples_ = 0;
  }

  void PerformanceWidget::AddFrameSample(long long sample)
  {
    if (sample > maxSample_)
    {
      maxSample_ = sample;
    }
    
    frameSamples_[currentIndex_] = sample;
    currentIndex_++;
    currentIndex_ %= MAX_FRAME_SAMPLES;
    numSamples_++;
  }
}