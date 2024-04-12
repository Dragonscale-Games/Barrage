/* ======================================================================== */
/*!
 * \file            TimelineWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Widget for displaying the game timeline.
 */
 /* ======================================================================== */

#include "TimelineWidget.hpp"
#include "Editor.hpp"

namespace Barrage
{
  static const unsigned MAX_TICKS = 7200;
  
  void TimelineWidget::Use()
  {
    unsigned& gameTick = Editor::Get().Data().gameTick_;

    ImGui::Begin("Timeline");

    if (ImGui::Button("<|"))
    {
      gameTick = 0;
      Editor::Get().Data().sceneIsDirty_ = true;
    }

    ImGui::InvisibleButton("##timeline", ImVec2(-1, -1));

    // This invisible button will be our timeline
    if (ImGui::IsItemActive())
    {
      // Get the mouse position, relative to the top left of the button
      ImVec2 pos = ImGui::GetMousePos();
      ImVec2 min = ImGui::GetItemRectMin();
      ImVec2 max = ImGui::GetItemRectMax();

      // Clamp pos.x between min.x and max.x
      pos.x = (pos.x < min.x) ? min.x : pos.x;
      pos.x = (pos.x > max.x) ? max.x : pos.x;

      // Calculate the selected value based on the click position
      float t = (pos.x - min.x) / (max.x - min.x); // will be 0..1 depending on position
      gameTick = static_cast<unsigned>(t * MAX_TICKS);
      Editor::Get().Data().sceneIsDirty_ = true;
    }

    // Get the bounds of the timeline again
    ImVec2 min = ImGui::GetItemRectMin();
    ImVec2 max = ImGui::GetItemRectMax();

    // Render a border around the timeline
    ImGui::GetWindowDrawList()->AddRect(min, max, IM_COL32(255, 255, 255, 255));

    // Render a vertical line at the selected position
    float t = gameTick / static_cast<float>(MAX_TICKS);
    float x = min.x + t * (max.x - min.x);
    ImVec2 line_start(x, min.y);
    ImVec2 line_end(x, max.y);
    ImGui::GetWindowDrawList()->AddLine(line_start, line_end, IM_COL32(255, 0, 0, 255), 1.0f);


    ImGui::End();
  }
}