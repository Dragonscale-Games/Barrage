/* ======================================================================== */
/*!
 * \file            Widget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base class for all editor widgets.
 */
 /* ======================================================================== */

#include "Widget.hpp"

namespace Barrage
{
  Widget::Widget(EditorData& editorData, Engine& engine) :
    editorData_(editorData),
    engine_(engine)
  {
  }
}