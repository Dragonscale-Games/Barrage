/* ======================================================================== */
/*!
 * \file            ScaleWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Widget for editing Scale components.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "ScaleWidget.hpp"
#include "GUI/GUI.hpp"

namespace Barrage
{
  ScaleWidget::ScaleWidget() :
    scaleComponent_(nullptr)
  {
  }

  void ScaleWidget::MakeWidget()
  {
    if (scaleComponent_ == nullptr)
    {
      return;
    }

    ImGui::PushID("Scale");
    ImGui::InputFloat("x", &scaleComponent_->data_[0].dimensions_.x);
    ImGui::InputFloat("y", &scaleComponent_->data_[0].dimensions_.y);
    ImGui::PopID();
  }

  void ScaleWidget::SetComponent(Component* component)
  {
    scaleComponent_ = dynamic_cast<Scale*>(component);
  }
}