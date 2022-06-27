/* ======================================================================== */
/*!
 * \file            SpriteWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here>

 */
 /* ======================================================================== */

#include "stdafx.h"
#include "SpriteWidget.hpp"
#include "GUI/GUI.hpp"

namespace Barrage
{
  SpriteWidget::SpriteWidget() :
    spriteComponent_(nullptr)
  {
  }

  void SpriteWidget::MakeWidget()
  {
    if (spriteComponent_ == nullptr)
    {
      return;
    }

    ImGui::Text("TODO: Implement sprite widget");
  }

  void SpriteWidget::SetComponent(Component* component)
  {
    spriteComponent_ = dynamic_cast<Sprite*>(component);
  }
}