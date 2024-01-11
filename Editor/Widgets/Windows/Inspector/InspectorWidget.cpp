/* ======================================================================== */
/*!
 * \file            InspectorWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Allows user to edit components for pools and game objects.
 */
 /* ======================================================================== */

#include "InspectorWidget.hpp"
#include "Editor.hpp"

namespace Barrage
{
  void InspectorWidget::Use()
  {
    ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_NoMove);

    ImGui::End();
  }
}