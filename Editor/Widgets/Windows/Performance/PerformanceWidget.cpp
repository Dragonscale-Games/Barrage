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
  long long PerformanceWidget::frameSamples_[PerformanceWidget::MAX_SAMPLES] = { 0 };
  long long PerformanceWidget::maxFrameSample_ = 0;
  size_t PerformanceWidget::currentFrameSampleIndex_ = 0;
  size_t PerformanceWidget::numFrameSamples_ = 0;
  long long PerformanceWidget::drawSamples_[PerformanceWidget::MAX_SAMPLES] = { 0 };
  long long PerformanceWidget::maxDrawSample_ = 0;
  size_t PerformanceWidget::currentDrawSampleIndex_ = 0;
  size_t PerformanceWidget::numDrawSamples_ = 0;

  void PerformanceWidget::Use()
  {
    float totalFrameTimes = 0;
    size_t numFrameSamples = numFrameSamples_ < MAX_SAMPLES ? numFrameSamples_ : MAX_SAMPLES;
    for (size_t i = 0; i < numFrameSamples; ++i)
    {
      totalFrameTimes += frameSamples_[i];
    }
    long long averageFrameTime = numFrameSamples > 0 ? static_cast<long long>(totalFrameTimes / numFrameSamples) : 0;

    float totalDrawTimes = 0;
    size_t numDrawSamples = numDrawSamples_ < MAX_SAMPLES ? numDrawSamples_ : MAX_SAMPLES;
    for (size_t i = 0; i < numDrawSamples; ++i)
    {
      totalDrawTimes += drawSamples_[i];
    }
    long long averageDrawTime = numDrawSamples > 0 ? static_cast<long long>(totalDrawTimes / numDrawSamples) : 0;

    ImGui::Begin("Performance");
    ImGui::Text("Frame time:     ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(averageFrameTime).c_str());

    ImGui::Text("Max frame time: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(maxFrameSample_).c_str());
    if (ImGui::Button("Reset##frametime"))
    {
      maxFrameSample_ = 0;
    }

    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::Text("Draw time:      ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(averageDrawTime).c_str());

    ImGui::Text("Max draw time:  ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(maxDrawSample_).c_str());
    if (ImGui::Button("Reset##drawtime"))
    {
      maxDrawSample_ = 0;
    }

    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::Text("Frame budget: 8333");
    ImGui::End();
  }

  void PerformanceWidget::Reset()
  {
    maxFrameSample_ = 0;
    currentFrameSampleIndex_ = 0;
    numFrameSamples_ = 0;

    maxDrawSample_ = 0;
    currentDrawSampleIndex_ = 0;
    numDrawSamples_ = 0;
  }

  void PerformanceWidget::AddFrameSample(long long sample)
  {
    if (sample > maxFrameSample_)
    {
      maxFrameSample_ = sample;
    }
    
    frameSamples_[currentFrameSampleIndex_] = sample;
    currentFrameSampleIndex_++;
    currentFrameSampleIndex_ %= MAX_SAMPLES;
    numFrameSamples_++;
  }

  void PerformanceWidget::AddDrawSample(long long sample)
  {
    if (sample > maxDrawSample_)
    {
      maxDrawSample_ = sample;
    }

    drawSamples_[currentDrawSampleIndex_] = sample;
    currentDrawSampleIndex_++;
    currentDrawSampleIndex_ %= MAX_SAMPLES;
    numDrawSamples_++;
  }
}