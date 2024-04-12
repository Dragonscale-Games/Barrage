/* ======================================================================== */
/*!
 * \file            GameWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Displays the current game scene.
 */
 /* ======================================================================== */

#include "GameWidget.hpp"
#include "Editor.hpp"

namespace Barrage
{
  void GameWidget::Use()
  {
    ImGui::Begin("Game", nullptr, ImGuiWindowFlags_NoMove);

    ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
    float imageWidth = contentRegionAvailable.x;
    float imageHeight = contentRegionAvailable.y;

    ImGui::Image((void*)(intptr_t)Engine::Get().Graphics().GetFramebuffer().GetFramebufferID(), ImVec2(imageWidth, imageHeight), ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
  }
}