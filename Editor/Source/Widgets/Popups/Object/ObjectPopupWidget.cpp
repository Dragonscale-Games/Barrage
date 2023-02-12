/* ======================================================================== */
/*!
 * \file            ObjectPopupWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The menu that pops up when you right click an object.
 */
 /* ======================================================================== */

#include "ObjectPopupWidget.hpp"

namespace Barrage
{
  void ObjectPopupWidget::Use(const char* strId)
  {
    if (!ImGui::BeginPopup(strId))
    {
      return;
    }

    ImGui::BeginDisabled();
    ImGui::Text("(Placeholder)");
    ImGui::EndDisabled();

    ImGui::EndPopup();
  }
}