/* ======================================================================== */
/*!
 * \file            PositionWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Widget for editing Position components.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "PositionWidget.hpp"
#include "GUI/GUI.hpp"

namespace Barrage
{
  PositionWidget::PositionWidget() :
    positionComponent_(nullptr)
  {
  }

  void PositionWidget::MakeWidget()
  {
    if (positionComponent_ == nullptr)
    {
      return;
    }

    ImGui::PushID("Position");
    ImGui::InputFloat("x", &positionComponent_->data_[0].position_.x);
    ImGui::InputFloat("y", &positionComponent_->data_[0].position_.y);
    ImGui::PopID();
  }

  void PositionWidget::SetComponent(Component* component)
  {
    positionComponent_ = dynamic_cast<Position*>(component);
  }
}