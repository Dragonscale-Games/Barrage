/* ======================================================================== */
/*!
 * \file            SpawnerWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here>

 */
 /* ======================================================================== */

#include "stdafx.h"
#include "SpawnerWidget.hpp"
#include "GUI/GUI.hpp"

namespace Barrage
{
  SpawnerWidget::SpawnerWidget() :
    spawnerComponent_(nullptr)
  {
  }

  void SpawnerWidget::MakeWidget()
  {
    if (spawnerComponent_ == nullptr)
    {
      return;
    }

    ImGui::Text("TODO: Implement spawner widget");
  }

  void SpawnerWidget::SetComponent(Component* component)
  {
    spawnerComponent_ = dynamic_cast<Spawner*>(component);
  }
}