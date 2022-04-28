/* ======================================================================== */
/*!
 * \file            TagsWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here>

 */
 /* ======================================================================== */

#include "stdafx.h"
#include "TagsWidget.hpp"
#include "GUI/GUI.hpp"

namespace Barrage
{
  TagsWidget::TagsWidget() :
    tagsComponent_(nullptr)
  {
  }

  void TagsWidget::MakeWidget()
  {
    if (tagsComponent_ == nullptr)
    {
      return;
    }

    ImGui::Text("TODO: Implement tags widget");
  }

  void TagsWidget::SetComponent(Component* component)
  {
    tagsComponent_ = dynamic_cast<Tags*>(component);
  }
}