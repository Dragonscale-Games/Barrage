/* ======================================================================== */
/*!
 * \file            DestructibleWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Widget for editing Destructible components.
 */
/* ======================================================================== */

#include "stdafx.h"
#include "DestructibleWidget.hpp"
#include "GUI/GUI.hpp"

namespace Barrage
{
  DestructibleWidget::DestructibleWidget() :
    destructibleComponent_(nullptr)
  {
  }

  void DestructibleWidget::MakeWidget()
  {
    if (destructibleComponent_ == nullptr)
    {
      return;
    }

    if (destructibleComponent_->data_[0].destroyed_)
    {
      ImGui::Text("Destroyed: True");
    }
    else
    {
      ImGui::Text("Destroyed: False");
    }
  }

  void DestructibleWidget::SetComponent(Component* component)
  {
    destructibleComponent_ = dynamic_cast<Destructible*>(component);
  }
}