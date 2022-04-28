/* ======================================================================== */
/*!
 * \file            RotationWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Widget for editing Rotation components.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "RotationWidget.hpp"
#include "GUI/GUI.hpp"

namespace Barrage
{
  RotationWidget::RotationWidget() :
    rotationComponent_(nullptr)
  {
  }

  void RotationWidget::MakeWidget()
  {
    if (rotationComponent_ == nullptr)
    {
      return;
    }

    ImGui::PushID("Rotation");
    ImGui::SliderAngle("angle", &rotationComponent_->data_[0].angle_, 0, 360.0f);
    ImGui::PopID();
  }

  void RotationWidget::SetComponent(Component* component)
  {
    rotationComponent_ = dynamic_cast<Rotation*>(component);
  }
}