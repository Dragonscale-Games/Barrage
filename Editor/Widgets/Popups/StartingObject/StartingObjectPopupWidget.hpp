/* ======================================================================== */
/*!
 * \file            StartingObjectPopupWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The menu that pops up when you right click a starting object.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef StartingObjectPopupWidget_BARRAGE_H
#define StartingObjectPopupWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <imgui/imgui.h>

namespace Barrage
{   
  //! Starting object right click menu
  class StartingObjectPopupWidget
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Adds the widget to the window.

        \param strId
          The ID passed to ImGui::OpenPopup() that tells this popup
          when to open.

        \param callback
          A function to be called when the popup closes.
      */
      /**************************************************************/
      static void Use(const char* strId);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // StartingObjectPopupWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////