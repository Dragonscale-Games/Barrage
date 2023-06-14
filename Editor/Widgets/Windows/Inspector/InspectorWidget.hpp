/* ======================================================================== */
/*!
 * \file            InspectorWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Allows user to edit components for pools and game objects.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef InspectorWidget_BARRAGE_H
#define InspectorWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <imgui/imgui.h>
#include <string_view>

namespace Barrage
{
  //! Allows user to modify components
  class InspectorWidget
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Adds the widget to the window.
      */
      /**************************************************************/
      static void Use();

      static ImVec2 GetSize();

    private:
      static ImVec2 InspectorWidget::size_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // InspectorWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////