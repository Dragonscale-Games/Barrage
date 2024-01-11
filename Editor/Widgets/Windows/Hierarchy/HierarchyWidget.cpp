/* ======================================================================== */
/*!
 * \file            HierarchyWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Displays all pools in current game scene.
 */
 /* ======================================================================== */

#include "HierarchyWidget.hpp"
#include "Editor.hpp"

namespace Barrage
{
  void HierarchyWidget::Use()
  {
    ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_NoMove);


    ImGui::End();
  }
}